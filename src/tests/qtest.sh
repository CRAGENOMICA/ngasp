# -p: linies per seqüència (1/2)
# -u: include unknown

rm a.txt
rm b.txt

# test 4
#                              tests/mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > a.txt
# build/binaries/mainExecutable/main mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > b.txt


# test 5

                             tests/mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > a.txt
build/binaries/mainExecutable/main mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > b.txt






diff a.txt b.txt
