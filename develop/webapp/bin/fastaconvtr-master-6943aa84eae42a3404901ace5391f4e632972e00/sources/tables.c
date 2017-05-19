#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

/*GAMMA and Chi-square FUNCTIONS */

double gammln(double zz)
{
	/*Based on Numerical Recipes in C, Press et al. 1992. p. 213. and on 
	Lanczos 1964 J. SIAM Numer. Anal. Ser. B, Vol. 1 pp 86-96.*/
	
	/*gamma distribution for a z integer*/
	double loggammaz;
	double z,logg,h,sumc;
	static double gamma = 5.0;
	static double c0 =  1.000000000178;
	static double c1 = 76.180091729406;
	static double c2 = 86.505320327112;
	static double c3 = 24.014098222230;
	static double c4 =  1.231739516140;
	static double c5 =  0.001208580030;
	static double c6 =  0.000005363820;
	
	if(zz <= 0.) {
		puts("Error gamma");
		return (double)-10000.;
	}
	
	z = (double)zz;
	h = (double)sqrt(2. * PI);
	sumc = c0 + c1/(z+1.) - c2/(z+2.) + c3/(z+3.)  - c4/(z+4.) + c5/(z+5.) - c6/(z+6.);
	logg = (z + 0.5)*(double)log((double)(z + gamma + 0.5)) - (z + gamma + 0.5);
	loggammaz = log((double)h);
	loggammaz += logg + log((double)sumc);
	loggammaz -= log((double)z);
	
	return (double)loggammaz;
}

#define ITMAX 1000
#define EPS 3.0e-7
void gser(double *gamser,double a, double x, double *gln)
{
    /*Returns the incomplete gamma function P(a,x) evaluated by its series
    representation as gamser. Also returns ln T(a) as gln. numerical recipes in C. 2nd ed. p. 218
    */
    double gammln(double xx);
    int n;
    double sum,del,ap;
    
    *gln = gammln(a);
    if(x <= (double)0.0) {
        if(x < (double)0.0) puts("\n\nError in gser. Gamma is not well calculated.");
        *gamser = (double)0.0;
        return;
    }
    else {
        ap = a;
        del = sum = (double)1.0/a;
        for(n=1;n<=ITMAX;n++) {
            ++ap;
            del *= x/ap;
            sum += del;
            if(fabs(del) < fabs(sum)*EPS) {
                *gamser = sum*(double)exp(-x+a*(double)log(x)-(*gln));
                return;
            }
        }
        puts("\n\nError in gser. Gamma is not well calculated. ITMAX too small.");
		*gamser = (double)-10000;
        return;
    }
}

#define FPMIN 1.0e-30

void gcf(double *gammcf, double a, double x, double *gln)
{
    /*
        Returns the incomplete gamma function Q(a,x) evaluated by its continued fraction
        representation as gammcf. also returns ln T(a) as gln. numerical recipes in C. 2nd ed. p. 218
    */
    double gammln(double xx);
    int i;
    double an,b,c,d,del,h;
    
    *gln = gammln(a);
    b = x + (double)1.0 - a;
    c = (double)1.0/(double)FPMIN;
    d = (double)1.0/b;
    h = d;
    
    for(i=1;i<=ITMAX;i++) {
        an = - i*(i-a);
        b += (double)2.0;
        d = an*d+b;
        if(fabs(d) < FPMIN) d = (double)FPMIN;
        c = b + an/c;
        if(fabs(c) < FPMIN) c = (double)FPMIN;
        d = (double)1.0/d;
        del = d*c;
        h *= del;
        if(fabs(del - (double)1.0) < EPS) break;
    }
    if(i > ITMAX) {
		puts("Error in gcf. Gamma is not well calculated. ITMAX too small.");
		*gammcf = (double)-10000;
	}
    *gammcf = (double)exp(-x+a*(double)log(x)-(*gln))*h;
}

double gammq( double a, double x)
{
    /*Returns the incomplete gamma function Q(a,x) == 1 - P(a,x).*/
    /*numerical recipes in C. 2nd ed. p. 218*/
    void gcf(double *gammcf, double a, double x, double *gln);
    void gser(double *gamser, double a, double x, double *gln);
    double gamser,gammcf,gln;
    
    if(x < (double)0.0 || a <= (double)0.0) return (double)-1.0;
    if(x < (a+1.0)) {
        gser(&gamser,a,x,&gln);
        return (double)1.0-gamser;
    }
    else {
        gcf(&gammcf,a,x,&gln);
        return gammcf;
    }
}

double probQ_chisquare(int dgf,  double chisq)
{
    double gammq( double, double);
	/* probability of a chi square Q(a,x). Counting from the value of chi to infinite.*/
    return gammq((double)dgf/(double)2.0,chisq/(double)2.0);
}


