#!/bin/sh
# Experiments from "runexamples_linux.sh"


############################################################
# Constants
############################################################


STARTING_TEST='>run test '
TEST_DESCRIPTION='Description: '
PREPARING_TEST='Praparing test...'
EXECUTING_TEST='Executing test...'
EVALUATING_TEST='Evaluating test...'
SKIP_TEST='Skip test.'
RED='\033[1;31m'
BLUE='\033[1;34m'
GREEN='\033[0;32m'
NO_COLOR='\033[0m'
TEST_OK='Result: Pass' 
TEST_ERROR='Result: Fail'
CLEANING_TEST='Cleaning test...'
MSTATSPOP_EXEC='/develop/webapp/bin/mstatspop'
NGASP_EXEC='/develop/webapp/bin/ngasp'
#NGASP_EXEC='../backend/Debug/ngaSP_backend'
INPUT_FILES_PATH='/develop/tests/examples'
NGASP_DOESNOT_EXIST='ngaSP executable not found. It is expected here: '
NGASP_EMPTY_FILE='Empty output from ngaSP'
SKIP_CLEAN_PREVIOUS_TESTS="Atention: Previous mstatspop outputs WON'T BE regenerated"


############################################################
# Global Variables
############################################################

clearPreviousTests=no

############################################################
# runTest Function
############################################################

runTest()
{
	echo -e $STARTING_TEST $numTest
	echo -e $TEST_DESCRIPTION $testDescription

	echo -e $PREPARING_TEST
	
		# Create the test folder
	
		if [ ! -d "test$numTest" ]; then
			mkdir test$numTest
		else
			# Remove the test folder contents

			if [ "$clearPreviousTests" == "yes" ]; then
				rm $mstatspopOutputFile
				rm $ngaSPOutputFile
				rm ./test$numTest/diff_result
			fi
		fi

	echo -e $EXECUTING_TEST

		# Execute mstatspop and ngaSP

		echo -e "$NGASP_EXEC mstatspop $fileParams $inputFile $experimentParams > $ngaSPOutputFile"
		$MSTATSPOP_EXEC $fileParams $inputFile $experimentParams > $mstatspopOutputFile
		$NGASP_EXEC mstatspop $fileParams $inputFile $experimentParams > $ngaSPOutputFile

	echo -e $EVALUATING_TEST

		# Compare outputs from both applications

		diff $mstatspopOutputFile $ngaSPOutputFile > ./test$numTest/diff_result
		if [[ -s ./test$numTest/diff_result ]] ; then

			# Outputs are different

			if [[ -s $ngaSPOutputFile ]] ; then

				# Show output differences

				echo -en $RED$TEST_ERROR$NO_COLOR
				echo -e ''
				echo -en $BLUE
				cat ./test$numTest/diff_result
				echo -en $NO_COLOR
			else
				# ngaSP does not output anything

				echo -en $RED$NGASP_EMPTY_FILE$NO_COLOR
				echo -e ''
			fi ;
			echo -e ''
		else
			echo -en $GREEN$TEST_OK$NO_COLOR
			echo -e ''
		fi ;
		echo -e ''
}


############################################################
# skip Function
############################################################

skipTest()
{
	echo -e $STARTING_TEST $numTest
	echo -e $TEST_DESCRIPTION $testDescription
	echo -e $GREEN$SKIP_TEST$NO_COLOR
}


############################################################
# main Function
############################################################

main()
{
	tput clear 
	echo '==============================================================================='
	echo '[ngaSP]: Testing Shell Script'
	echo '==============================================================================='
	echo -e ''

	if [ "$clearPreviousTests" == "no" ]; then
		echo -en $GREEN$SKIP_CLEAN_PREVIOUS_TESTS$NO_COLOR
		echo -e ''
		echo -e ''
	fi	

	if [ ! -f $NGASP_EXEC ] ; then
		echo -en $RED$NGASP_DOESNOT_EXIST$NGASP_EXEC$NO_COLOR
		echo -e ''
	else

		############################################################
		# New Test
		############################################################

		#../bin/mstatspop -f fasta -i ./100Kchr10.fa -o 0 -N 1 42    -T ../Results/mstatspop_100chr10.fa.01.txt -K 1 -n chr10.txt
		numTest=001
		testDescription='Example fa.01.txt'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/100Kchr10.fa
		experimentParams='-o 0 -N 1 42 -K 1 -n /develop/tests/examples/chr10.txt'
		mstatspopOutputFile=./test$numTest/mstatspop_100chr10.fa.01.txt
		ngaSPOutputFile=./test$numTest/mstatspop_100chr10.fa.01_ngaSP.txt
		runTest
	fi ;
	#Todo: lo pongo para probar solo el primer test
	if False ; then
		
	    ############################################################
		# Test
		############################################################

		numTest=1
		testDescription='Run for a single population'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-N 1 48 -n $INPUT_FILES_PATH/MC1R.txt'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_One_Pop_Total.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_One_Pop_Total_ngaSP.txt
		runTest

		############################################################
		# Test
		############################################################

		numTest=2
		testDescription='analyze a fasta file with 2 pops (48 and 46 individuals) and NO outgroup, erasing columns with missing values, 1000 permutations to calculate P-values with Fst, seed 123456.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 0 -p 1 -u 0 -t 1000 -s 123456 -G 0 -N 2 48 46 -n $INPUT_FILES_PATH/MC1R.txt'
		mstatspopOutputFile=./test$numTest/MC1R_PigsNOOutg_Total.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsNOOutg_Total_ngaSP.txt	
	        runTest


		############################################################
		# Test
		############################################################

		numTest=3
		testDescription='analyze a fasta file with 2 pops (48 and 46 individuals) plus one outgroup, erasing columns with missing values, 1000 permutations to calculate P-values with Fst, seed 123456.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_Total.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_Total_ngaSP.txt	
		runTest


		############################################################
		# Test
		############################################################

		numTest=4
		testDescription='same analysis but considering only nonsynonymous positions in coding regions. We use the option -g and include a GTF/GFF file.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt -g $INPUT_FILES_PATH/MC1R.gff nonsynonymous Nuclear_Universal'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_NSyn.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_ngaSP.txt	
		runTest


		############################################################
		# Test
		############################################################

		numTest=5
		testDescription='in this analysis we consider that each sequence is coming from one diploid individual (double number of lines). IUPAC symbols are allowed (K,W,S,R,M,Y). Haplotype-relaated analysis are not performed.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt -g $INPUT_FILES_PATH/MC1R.gff nonsynonymous Nuclear_Universal'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_diploidseqs.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_diploidseqs_ngaSP.txt	
		runTest

		############################################################
		# Test
		############################################################

		numTest=6
		testDescription='analysis considering columns with missing values. In that case we do not consider (or we do not have) the outgroup. Haplotype-relaated analysis are not performed.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned_Ns.fas
		experimentParams='-o 0 -p 1 -u 1 -t 1000 -s 123456 -G 0 -N 2 48 46 -n $INPUT_FILES_PATH/MC1R.txt -g $INPUT_FILES_PATH/MC1R.gff nonsynonymous Nuclear_Universal'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_missing_nooutg.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_missing_nooutg_ngaSP.txt	
		runTest

		############################################################
		# Test
		############################################################

		numTest=7
		testDescription='analysis considering columns with missing values and in diploid sequences. Haplotype-relaated analysis are not performed.'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned_Nsdiploid.fas
		experimentParams='-o 0 -p 2 -u 1 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt -g $INPUT_FILES_PATH/MC1R.gff nonsynonymous Nuclear_Universal'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_missing_diploid.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_missing_diploid_ngaSP.txt	
		runTest

		############################################################
		# Test
		############################################################

		numTest=8
		testDescription='Output a table with SNPs (rows) and lineages (columns) using 0 1 and 9 (missing)'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 6 -p 1 -u 0 -t 1000 -s 123456 -G 0 -N 2 48 46 -n $INPUT_FILES_PATH/MC1R.txt'
		mstatspopOutputFile=./test$numTest/MC1R_PigsNOOutg_Total_SNPTable.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsNOOutg_Total_SNPTable_ngaSP.txt	
		runTest

		############################################################
		# Test
		############################################################

		numTest=9
		testDescription='Run mstatspop and calculate Optimal tests: You must give a file with the expected frequency spectrum for the alternative model (always choosen previously, not a posteriori).'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt -a $INPUT_FILES_PATH/MC1R_H1frq.txt -g ../examples/MC1R.gff nonsynonymous Nuclear_Universal'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_Opttest.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_NSyn_Opttest_ngaSP.txt	
		runTest

		############################################################
		# Test
		############################################################

		numTest=10
		testDescription='Shows the frequency spectrum in "dadi" format'
		fileParams='-f fasta -i'
		inputFile=$INPUT_FILES_PATH/MC1R_PigsOutg_aligned.fas
		experimentParams='-o 3 -N 3 48 46 1 -n $INPUT_FILES_PATH/MC1R.txt -G 1'
		mstatspopOutputFile=./test$numTest/MC1R_PigsOutg_Two_Pop_Outg_Total_TableFreq.txt
		ngaSPOutputFile=./test$numTest/MC1R_PigsOutg_Two_Pop_Outg_Total_TableFreq_ngaSP.txt	
		runTest

	fi ;

	############################################################
	# End
	############################################################

	echo -e ''
}

main


# NEXT EXPERIMENTS

#Run mstatspop in a pipeline with ms: (in case ms coalescent simulator (Hudson, Bioinformatics 2002) is installed in your computer)
#In this case, we simulate the nonsynonymous positions from the entire gene MC1R by filtering only the positions included in the mask file.
####./ms 95 100 -t 10 -I 3 48 46 1 0 -ej 1e.0 2 1 -ej 2.0 3 1 | ./mstatspop -f ms -o 1 -p 1 -u 0 -m ../examples/MC1R_PigsOutg_aligned_npop3_nsam95_nonsynonymous_mask.txt -v 0.75 -s 34645 -l 965 -t 100 -G 1 -N 3 48 46 1 > ../outputs/MC1R_PigsOutg_NSyn_msrun.txt

#Run mstatspop using a ms-format file. We filter some interesting columns with "cut" (count first the positions of interest, it depends on the number of pops): 
####./mstatspop -f ms -i ../examples/MC1R_ms_simulation.txt -o 1 -p 1 -u 0 -m ../examples/MC1R_PigsOutg_aligned_npop3_nsam95_nonsynonymous_mask.txt -v 0.75 -s 34645 -l 965 -t 100 -G 1 -N 3 48 46 1 -a ../examples/MC1R_H1frq.txt > ../outputs/MC1R_PigsOutg_NSyn_msfile.txt 
####./mstatspop -f ms -i ../examples/MC1R_ms_simulation.txt -o 1 -p 1 -u 0 -m ../examples/MC1R_PigsOutg_aligned_npop3_nsam95_nonsynonymous_mask.txt -v 0.75 -s 34645 -l 965 -t 100 -G 1 -N 3 48 46 1 -a ../examples/MC1R_H1frq.txt | cut -f 59,60,61,62,63,64,125,126,127,128,129,130  ####> ../outputs/MC1R_PigsOutg_NSyn_cut_msfile.txt 

#Run mstatspop using a ms-format file. We do an analysis over one population simulated and force analysis with outgroup and without. The last example keep the desired columns detailed in a file (using a perl script with the file required_columns1.txt):
####./mstatspop -f ms -i ../examples/ms_one_pop_simulation.txt -o 1 -p 1 -u 0 -m -1 -v 0.5 -s 57354 -l 1000 -t 100 -G 0 -F 1 -q 0.01 -N 1 20 > ../outputs/ms_one_pop_results_force_outgroup.txt 
####./mstatspop -f ms -i ../examples/ms_one_pop_simulation.txt -o 1 -p 1 -u 0 -m -1 -v 0.5 -s 57354 -l 1000 -t 100 -N 1 20 > ../outputs/ms_one_pop_results_no_outgroup.txt 
####./mstatspop -f ms -i ../examples/ms_one_pop_simulation.txt -o 1 -p 2 -u 0 -m -1 -v 0.5 -s 57354 -l 1000 -t 100 -N 1 20 > ../outputs/ms_one_pop_diploid_results_no_outgroup.txt 
####perl ./collect_data_columns.pl -in ../outputs/ms_one_pop_diploid_results_no_outgroup.txt -fc ../examples/required_columns1.txt > ../outputs/ms_one_pop_diploid_results_no_outgroup_Selected_Columns.txt

#Comparing the analysis of mstatspop from the same source file using ms or fasta:
####./mstatspop -f fasta -i ../examples/MC1R_PigsOutg_aligned_Ns.fas -o 0 -p 1 -u 1 -t 1000 -s 123456 -G 1 -N 3 48 46 1  > ../outputs/MC1R_PigsOutg_missing_fasta.txt
####./fastagff2ms -i ../examples/MC1R_PigsOutg_aligned_Ns.fas -f e -p 1 -o 1 > ../outputs/MC1R_PigsOutg_aligned_Ns_ms.txt
####./mstatspop -f ms_e -i ../outputs/MC1R_PigsOutg_aligned_Ns_ms.txt -o 0 -p 1 -u 1 -t 1 -s 123456 -G 1 -N 3 48 46 1 -l 944 -v 5 -x 0.04  > ../outputs/MC1R_PigsOutg_missing_ms.txt

#Do a "genomic" analysis using fastagff2ms to cut the genome in windows and HKAdirect to calculate HKA test:
####./fastagff2ms -i ../examples/H100N10_EACH.cov2X.rep1.ok.ms.iupac_missing.fas -f e -p 2 -o 1 -w 10000 -s 10000 > ../outputs/H100N10_ms10000extended_ploidy_missing_outg.txt
####./mstatspop -f ms_e -i ../outputs/H100N10_ms10000extended_ploidy_missing_outg.txt -o 1 -p 2 -u 1 -m -1 -v 0.513 -l 10000 -t 100 -N 2 18 2 -s 2545 -x 0.0000351 -G 1 -k 0 > ../outputs/H100N10_ms10000extended_ploidy_missing_outg_mstatspop.txt
####perl mstatspop2HKA.pl -in ../outputs/H100N10_ms10000extended_ploidy_missing_outg_mstatspop.txt > ../outputs/H100N10_ms10000extended_ploidy_missing_outg_HKA.txt
####./HKAdirect ../outputs/H100N10_ms10000extended_ploidy_missing_outg_HKA.txt > ../outputs/H100N10_ms10000extended_ploidy_missing_outg_HKA_Results.txt

#Do a "genomic" analysis using nGDcallwe to cut the genome (mpileup format) in windows and use HKAdirect to calculate HKA test:
####cat ../examples/POP_ind_all_txt.mpileup | perl ./NGHcaller.pl -mindep=2 -maxdep=50 -wlen=200 -platform=33 -baseq=20 -greads=6 > ../outputs/POP_ind_all_txt.mse
####./mstatspop -f ms_e -i ../outputs/POP_ind_all_txt.mse -o 1 -p 2 -u 1 -m -1 -v 0.513 -l 200 -t 5 -N 2 16 1 -s 2545 -x 0.076875 -G 1 -k 0 > ../outputs/POP_ind_all_txt_mstatspop.txt
####perl mstatspop2HKA.pl -in ../outputs/POP_ind_all_txt_mstatspop.txt > ../outputs/POP_ind_all_txt_mstatspop_outg_HKA.txt
####./HKAdirect ../outputs/POP_ind_all_txt_mstatspop_outg_HKA.txt > ../outputs/POP_ind_all_txt_mstatspop_outg_HKA_Results.txt







