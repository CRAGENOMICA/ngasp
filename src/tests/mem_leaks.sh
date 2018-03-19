echo Test Memory Leaks
rm sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input.fa -N 1 48 > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 0 -N 2 48 46 > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/MC1R_PigsOutg_aligned.fa -o 0 -p 2 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input_ns.fa -o 0 -p 1 -u 1 -t 1000 -s 123456 -G 0 -N 2 48 46 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input_nsdiploid.fa -o 0 -p 2 -u 1 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -g examples/MC1R.gff nonsynonymous Nuclear_Universal > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input.fa -o 6 -p 1 -u 0 -t 1000 -s 123456 -G 0 -N 2 48 46 > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/MC1R.fa -o 0 -p 1 -u 0 -t 1000 -s 123456 -G 1 -N 3 48 46 1 -a examples/MC1R_H1frq.txt -g examples/MC1R.gff nonsynonymous Nuclear_Universal > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f fasta -i examples/input.fa -o 3 -N 3 48 46 1 -G 1 > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f ms -i examples/ms_one_pop_simulation.txt -o 1 -p 1 -u 0 -v 0.5 -s 57354 -l 1000 -t 100 -G 0 -F 1 -q 0.01 -N 1 20 -m examples/MC1R_PigsOutg_aligned_npop3_nsam95_nonsynonymous_mask.txt > sortida.txt
valgrind --leak-check=full --show-leak-kinds=all build/binaries/mainExecutable/main mstatspop -f ms -i examples/ms_one_pop_simulation.txt -o 1 -p 1 -u 1 -x 0.04 -v 0.5 -s 57354 -l 1000 -t 100 -G 0 -F 1 -q 0.01 -N 1 20 -m examples/MC1R_PigsOutg_aligned_npop3_nsam95_nonsynonymous_mask.txt > sortida.txt
rm sortida.txt
