echo '*****************************************************************************'
sed ':a;N;$!ba;s/ \_\n/ /g' mstatspop.ngasp > m1.txt      # substituir " _EOL" per "" (http://stackoverflow.com/questions/1251999/how-can-i-replace-a-newline-n-using-sed)
sed -e 's/#.*//' -e '/^$/d' -e '/^ *$/d' m1.txt > m2.txt  # substituir "#...." per "", esborrar les linies buides i esborrar les linies que nomès tenen espais
sed -e 's/ \+ / /g' -e 's/^ //' -e 's/"//g' m2.txt > m3.txt          # substituir molts espais per un de sol, treure l'espai que tenen totes les linies al començament i treure totes les cometes dobles
sed -e 's/dim -n /CreateVariable("/' -e 's/calc -n /CreateCalc("/' -e 's/if --ref /CreateIf("/' -e 's/endif/CreateEndIf("/' -e 's/end-for/CreateEndFor("/' -e 's/del -n /CreateRemoveVariable("/' -e 's/set --to /AssignValue("/' -e 's/ --eq /", "EQ", "/g' -e 's/ --or --ref /", "OR", "/g'  -e 's/ --and --ref /", "AND", "/g' -e 's/ --ne /", "NE", "/g' -e 's/ --gt /", "GT", "/g' -e 's/ --lt /", "LT", "/g' -e 's/ --eq /", "EQ", "/' -e 's/ --add /", "ADD", "/'  -e 's/ --sub /", "SUB", "/'  -e 's/ --mul /", "MUL", "/'  -e 's/ --div /", "DIV", "/' -e 's/ --as /", "/' -e 's/$/");/' -e 's/run -n /Execute("/' -e 's/for --ite /CreateFor("/' -e 's/ --from /", "/' -e 's/ --to /", "/' -e 's/ --inc /", "/' -e 's/print .*//' -e 's/@LOAD_VALUES.*//' -e 's/const --name /CreateConstant("/' -e 's/ --by /", "/' -e 's/exit/CreateExit("/' -e 's/else/CreateElse("/' -e 's/reserve -n /CreateReserve("/' -e 's/ --len /","/' -e 's/ --default /","/' -e 's/ --regs /", "/' -e 's/ --tables /", "/' -e 's/, ""/, "/' -e 's/"");/");/g' -e 's/" ");/"");/' -e 's/, /,/g'    -e 's/(");/();/' m3.txt > m4.txt # -e 's/\"\"/\"/g' -e 's/("");/();/'
#sed -e 's/dim -n /CreateVariable("/' -e 's/calc -n /CreateCalc("/' -e 's/if --ref /CreateIf("/' -e 's/endif/CreateEndIf("/' -e 's/end-for/CreateEndFor("/' -e 's/del -n /CreateRemoveVariable("/' -e 's/set --to /AssignValue("/' -e 's/ --eq /", "EQ", "/g' -e 's/ --or --ref /", "OR", "/g' -e 's/\"\"/\"/g'  -e 's/ --and --ref /", "AND", "/g' -e 's/ --ne /", "NE", "/g' -e 's/ --gt /", "GT", "/g' -e 's/ --lt /", "LT", "/g' -e 's/ --eq /", "EQ", "/' -e 's/ --add /", "ADD", "/'  -e 's/ --sub /", "SUB", "/'  -e 's/ --mul /", "MUL", "/'  -e 's/ --div /", "DIV", "/' -e 's/ --as /", "/' -e 's/$/");/' -e 's/run -n /Execute("/' -e 's/for --ite /CreateFor("/' -e 's/ --from /", "/' -e 's/ --to /", "/' -e 's/ --inc /", "/' -e 's/print .*//' -e 's/@LOAD_VALUES.*//' -e 's/const --name /CreateConstant("/' -e 's/ --by /", "/' -e 's/exit/CreateExit("/' -e 's/else/CreateElse("/' -e 's/reserve -n /CreateReserve("/' -e 's/ --len /","/' -e 's/ --default /","/' -e 's/ --regs /", "/' -e 's/ --tables /", "/' -e 's/, ""/, "/' -e 's/"");/");/g' -e 's/" ");/"");/' -e 's/, /,/g' -e 's/(");/();/' -e 's/("");/();/' -e 's/,");/);/' m3.txt > m4.txt
# sed -e 's/s,i,l,e,n,t);/s,i,l,e,n,t");/' -e 's/U,n,i,v,e,r,s,a,l);/U,n,i,v,e,r,s,a,l");/' -e 's/D,r,o,s,o,p,h,i,l,a);/D,r,o,s,o,p,h,i,l,a");/' -e 's/M,a,m,m,a,l,s);/M,a,m,m,a,l,s");/' m4.txt > m5.txt
sed -e 's/("EMPTY_STRING",");/("EMPTY_STRING","");/' m4.txt > m5.txt
sed -e '/^$/d' m5.txt > m6.txt  # esborrar les linies buides
echo '*****************************************************************************'

cat conversor.html > result.html
cat m6.txt >> result.html
cat conversor2.html >> result.html



xdg-open "result.html" >/dev/null

