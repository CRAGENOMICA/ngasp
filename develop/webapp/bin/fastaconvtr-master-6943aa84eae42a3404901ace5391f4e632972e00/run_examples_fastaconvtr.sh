##fastaconvtr v0.1beta (20161219) Sebastian E. Ramos-Onsins.
#
#Flags:
#      -F [input format file: f (fasta), t (tfasta)]
#      -i [path and name of the input file]
#      -f [output format file: t (tfasta), f (fasta), m (ms)]
#      -o [path and name of the output file]
#   OPTIONAL PARAMETERS:
#      -h [help and exit]
#      -P [define window lengths in 'physical' positions (1) or in 'effective' positions (0)]. DEFAULT: 1
#      -O [#_nsam] [Reorder samples: number order of first sample, number 0 is the first sample] [second sample] ...etc.
#      -W [for ms and fasta outputs, file with the coordinates of each window: (one header plus nlines with init end]
#      -N [#_pops] [#samples_pop1] ... [#samples_popN] (necessary in case to indicate the outgroup population)
#      -G [outgroup included (1) or not (0), last population (1/0)]. DEFAULT: 0
#      -u [Missing counted (1) or not (0) in weights given GFF annotation]. DEFAULT: 0
#      -m [masking regions: file indicating the start and the end of regions to be masked by Ns]
#     Outputing ms format:
#      -w [window size]. DEFAULT: Total_length
#      -s [slide size]. DEFAULT: Total_length
#     Inputing fasta format:
#      -p [if fasta input, haplotype:1 (single sequence) genotype:2 (two mixed sequences in IUPAC). DEFAULT: 1
#     Annotation file and weight options:
#      -g [GFF_file]
#         [add also: coding,noncoding,synonymous,nonsynonymous,silent,others(whatever annotated)]
#         [if 'silent', 'synonymous' or 'nonsynonymous' add: Genetic_Code: Nuclear_Universal,mtDNA_Drosophila,mtDNA_Mammals,Other]
#         [if 'Other', introduce the single letter code for the 64 triplets in the order UUU UUC UUA UUG ... etc.]
#      -c [in case use coding regions, criteria to consider transcripts (max/min/first/long)]. DEFAULT: long
#      -E [instead -g & -c, input file with weights for positions: include three columns with a header, first the physical positions (1...end), second the weight for positions and third a boolean weight for the variant (eg. syn variant but nsyn position)]
#
#Example files
#-i ./100Kchr10.fa 
#-i ./100Kchr10.tfa 
#-g ./100Kchr10.gtf
#-W ./coord_100Kb.txt 

#To compile:
gcc ./sources/*.c -lm -o ./bin/fastaconvtr -Wall -O3 -g -O0 -lz
cd ./Examples

../bin/fastaconvtr -h > ../fastaconvtr_help.txt

#FASTA TO TFASTA 
echo --------------------------------------------------------------------------------------------------
echo fasta to tfasta: Useful to run mstatspop in sliding windows mode. Also generates a weighting file.
echo --------------------------------------------------------------------------------------------------

echo
echo fa2tfa.ex01
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10.tfa.gz 
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10.tfa.gz 
echo
echo fa2tfa.ex01b masking several regions with Ns
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_01B.tfa.gz -m ./coord_100Kb.txt
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_01B.tfa.gz -m ./coord_100Kb.txt
echo
echo fa2tfa.ex02
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_02.tfa.gz  -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_fa2tfa_02.log.txt
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_02.tfa.gz  -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_fa2tfa_02.tfa.gz.log.txt
echo
echo fa2tfa.ex03 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_03.tfa.gz  -E ./100Kchr10_fa2tfa_02.tfa.gz_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_03.tfa.gz  -E ./100Kchr10_fa2tfa_02.tfa.gz_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo fa2tfa.ex02B
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_02B.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2tfa_02B.tfa.gz.log.txt
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_02B.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2tfa_02B.tfa.gz.log.txt
echo
echo fa2tfa.ex03B should give same results than previous
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_03B.tfa.gz -E ./100Kchr10_fa2tfa_02B.tfa.gz_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_03B.tfa.gz -E ./100Kchr10_fa2tfa_02B.tfa.gz_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo fa2tfa.ex04
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_04.tfa.gz -p 2
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_04.tfa.gz -p 2
echo
echo fa2tfa.ex05
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_05.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2 > ./100Kchr10_fa2tfa_05.tfa.gz.log.txt
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_05.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2 > ./100Kchr10_fa2tfa_05.tfa.gz.log.txt
echo
echo fa2tfa.ex06 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_06.tfa.gz -E ./100Kchr10_fa2tfa_05.tfa.gz_npops1_nsam84_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_06.tfa.gz -E ./100Kchr10_fa2tfa_05.tfa.gz_npops1_nsam84_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
echo
echo fa2tfa.ex07
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_07.tfa.gz -N 2 40 2 -G 1 -u 1
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_07.tfa.gz -N 2 40 2 -G 1 -u 1
echo
echo fa2tfa.ex08
echo ../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_08.tfa.gz -N 2 40 2 -G 1 -u 1 -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max > ./100Kchr10_fa2tfa_08.tfa.gz.log.txt
../bin/fastaconvtr -F fasta -f tfasta  -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_08.tfa.gz -N 2 40 2 -G 1 -u 1 -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max > ./100Kchr10_fa2tfa_08.tfa.gz.log.txt
echo
#echo fa2tfa.ex06
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_04.tfa.gz -W ./coord_100Kb.txt
#echo fa2tfa.ex07
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_05.tfa.gz -w 10000 -s 20000
#echo fa2tfa.ex08
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_06.tfa.gz -P 0
#echo fa2tfa.ex12
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_10.tfa.gz -W ./coord_100Kb.txt -p 2
#echo fa2tfa.ex13
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_01.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -W ./coord_100Kb.txt -P 0 
#echo fa2tfa.ex14 should give same results than previous
#../bin/fastaconvtr -F fasta -f tfasta -i ./100Kchr10.fa -o ./100Kchr10_fa2tfa_12.tfa.gz -E ./100Kchr10_fa2tfa_11.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.txt -P 0 -p 2

#FASTA TO FASTA
echo --------------------------------------------------------------------------------------------------
echo fasta to fasta: Useful for concatenate different regions from coordenates file. Also generating weighting file from GFF file
echo --------------------------------------------------------------------------------------------------
echo
echo fa2fa.ex01 should give same results than input
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_01.fa 
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_01.fa 
echo
echo fa2fa.ex01B should give same results than input
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10_tfa2fa_01.fa -o ./100Kchr10_fa2fa_01B.fa
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10_tfa2fa_01.fa -o ./100Kchr10_fa2fa_01B.fa
echo
echo fa2fa.ex02
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_02.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_fa2fa_02.fa.log.txt
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_02.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_fa2fa_02.fa.log.txt
echo
echo fa2fa.ex02B
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_02B.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2fa_02B.fa.log.txt
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_02B.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2fa_02B.fa.log.txt
echo
echo fa2fa.ex03 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_03.fa -E ./100Kchr10_fa2fa_02.fa_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_03.fa -E ./100Kchr10_fa2fa_02.fa_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo fa2fa.ex03B should give same results than previous
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_03B.fa -E ./100Kchr10_fa2fa_02B.fa_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_03B.fa -E ./100Kchr10_fa2fa_02B.fa_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo fa2fa.ex04
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_04.fa -W ./coord_100Kb.txt
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_04.fa -W ./coord_100Kb.txt
echo
echo fa2fa.ex05
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_05.fa -p 2
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_05.fa -p 2
echo
echo fa2fa.ex06
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_06.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2 > ./100Kchr10_fa2fa_06.fa.log.txt
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_06.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2 > ./100Kchr10_fa2fa_06.fa.log.txt
echo
echo fa2fa.ex07 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_07.fa -E ./100Kchr10_fa2fa_06.fa_npops1_nsam84_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
../bin/fastaconvtr -F fasta -f fasta   -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_07.fa -E ./100Kchr10_fa2fa_06.fa_npops1_nsam84_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
echo
#echo fa2fa.ex08
#../bin/fastaconvtr -F fasta -f fasta -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_05.fa -w 10000 -s 20000
#echo fa2fa.ex09
#../bin/fastaconvtr -F fasta -f fasta -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_06.fa -P 0
#echo fa2fa.ex13
#../bin/fastaconvtr -F fasta -f fasta -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_10.fa -W ./coord_100Kb.txt -p 2
#echo fa2fa.ex14
#../bin/fastaconvtr -F fasta -f fasta -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_11.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -W ./coord_100Kb.txt -P 0 
#echo fa2fa.ex15 should give same results than previous
#../bin/fastaconvtr -F fasta -f fasta -i ./100Kchr10.fa -o ./100Kchr10_fa2fa_12.fa -E ./100Kchr10_fa2tfa_11.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.txt -P 0 -p 2

#FASTA TO MS
echo --------------------------------------------------------------------------------------------------
echo fasta to ms: Useful to generate mask files in case doing simulations. msfile contains only variants in full-non-missing positions
echo --------------------------------------------------------------------------------------------------
echo
echo fa2ms.ex01
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_01.ms.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_01.ms.txt
echo
echo fa2ms.ex02
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_02.ms.txt -N 1 42
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_02.ms.txt -N 1 42
echo
echo fa2ms.ex03
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_03.ms.txt -N 2 40 2 -G 1
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_03.ms.txt -N 2 40 2 -G 1
echo
echo fa2ms.ex03B
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_03B.ms.txt -N 2 80 4 -G 1 -p 2
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_03B.ms.txt -N 2 80 4 -G 1 -p 2
echo
echo fa2ms.ex04
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_04.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2ms_04.ms.txt.log.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_04.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_fa2ms_04.ms.txt.log.txt
echo
echo fa2ms.ex05 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_05.ms.txt -E ./100Kchr10_fa2ms_04.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_05.ms.txt -E ./100Kchr10_fa2ms_04.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo fa2ms.ex06
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_06.ms.txt -W ./coord_100Kb.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_06.ms.txt -W ./coord_100Kb.txt
echo
echo fa2ms.ex06b should give same results than previous
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_06b.ms.txt -w 10000 -s 20000
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_06b.ms.txt -w 10000 -s 20000
echo
echo fa2ms.ex07
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_07.ms.txt -N 2 40 2 -w 10000 -s 20000
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_07.ms.txt -N 2 40 2 -w 10000 -s 20000
echo
echo fa2ms.ex08
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_08.ms.txt -P 0
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_08.ms.txt -P 0
echo
echo fa2ms.ex09
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_09.ms.txt -p 2
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_09.ms.txt -p 2
echo
echo fa2ms.ex10
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_10.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2 > ./100Kchr10_fa2ms_10.ms.txt.log.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_10.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2 > ./100Kchr10_fa2ms_10.ms.txt.log.txt
echo
echo fa2ms.ex11 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_11.ms.txt -E ./100Kchr10_fa2ms_10.ms.txt_npops1_nsam84_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_11.ms.txt -E ./100Kchr10_fa2ms_10.ms.txt_npops1_nsam84_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy2_WEIGHTS.gz -p 2
echo
echo fa2ms.ex12
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_12.ms.txt -W ./coord_100Kb.txt -p 2
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_12.ms.txt -W ./coord_100Kb.txt -p 2
echo
echo fa2ms.ex13
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_13.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -W ./coord_100Kb.txt -P 0 > ./100Kchr10_fa2ms_13.ms.txt.log.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_13.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -W ./coord_100Kb.txt -P 0 > ./100Kchr10_fa2ms_13.ms.txt.log.txt
echo
echo fa2ms.ex14 should give same results than previous
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_14.ms.txt -E ./100Kchr10_fa2ms_13.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.gz -P 0 -p 2 -W ./coord_100Kb.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_14.ms.txt -E ./100Kchr10_fa2ms_13.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.gz -P 0 -p 2 -W ./coord_100Kb.txt
echo
echo fa2ms.ex15
echo ../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_15.ms.txt -N 3 40 40 4 -G 1 -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2 > ./100Kchr10_fa2ms_15.ms.txt.log.txt
../bin/fastaconvtr -F fasta -f ms      -i ./100Kchr10.fa -o ./100Kchr10_fa2ms_15.ms.txt -N 3 40 40 4 -G 1 -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2 > ./100Kchr10_fa2ms_15.ms.txt.log.txt
echo

#TFASTA TO MS
echo --------------------------------------------------------------------------------------------------
echo tfasta to ms: Useful to generate mask files in case doing simulations. msfile contains only variants in full-non-missing positions
echo --------------------------------------------------------------------------------------------------
echo
echo tfa2ms.ex01
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_01.ms.txt
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_01.ms.txt
echo
echo tfa2ms.ex02
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_02.ms.txt -N 1 42
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_02.ms.txt -N 1 42
echo
echo tfa2ms.ex03
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_03.ms.txt -N 2 40 2 -G 1
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_03.ms.txt -N 2 40 2 -G 1
echo
echo tfa2ms.ex04
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_04.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2ms_04.ms.txt.log.txt
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_04.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2ms_04.ms.txt.log.txt
echo
echo tfa2ms.ex05 should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_05.ms.txt -E ./100Kchr10_tfa2ms_04.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.txt
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_05.ms.txt -E ./100Kchr10_tfa2ms_04.ms.txt_npops1_nsam42_nonsynonymous_max_ExcludeMissingmhits_NOoutg_ploidy1_WEIGHTS.txt
echo
echo tfa2ms.ex06
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_06.ms.txt -W ./coord_100Kb.txt
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_06.ms.txt -W ./coord_100Kb.txt
echo
echo tfa2ms.ex07 should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_07.ms.txt -w 10000 -s 20000
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_07.ms.txt -w 10000 -s 20000
echo
echo tfa2ms.ex08
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_08.ms.txt -P 0
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_08.ms.txt -P 0
echo
echo tfa2ms.ex09
echo ../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_09.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -W ./coord_100Kb.txt -P 0 > ./100Kchr10_tfa2ms_09.ms.txt.log.txt
../bin/fastaconvtr -F tfasta -f ms     -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_09.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -W ./coord_100Kb.txt -P 0 > ./100Kchr10_tfa2ms_09.ms.txt.log.txt
echo
#echo tfa2ms.ex04
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_03B.ms.txt -N 2 80 4 -G 1 -p 2
#echo tfa2ms.ex10
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_09.ms.txt -p 2
#echo tfa2ms.ex11
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_10.ms.txt -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2
#echo tfa2ms.ex12 should give same results than previous
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_11.ms.txt -E ./100Kchr10_tfa2ms_10.ms_nonsynonymous_max_ExcludeMissing_NOoutg_ploidy2_WEIGHTS.gz -p 2
#echo tfa2ms.ex13
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_12.ms.txt -W ./coord_100Kb.txt -p 2
#echo tfa2ms.ex15 should give same results than previous
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_14.ms.txt -E ./100Kchr10_tfa2ms_13.ms_nonsynonymous_max_ExcludeMissing_NOoutg_ploidy1_WEIGHTS.gz -P 0 -p 2
#echo tfa2ms.ex16
#../bin/fastaconvtr -F tfasta -f ms -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2ms_15.ms.txt -N 3 40 40 4 -G 1 -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 -p 2

#TFASTA TO FASTA
echo --------------------------------------------------------------------------------------------------
echo tfasta to fasta: Useful to generate a weighting file from GFF file
echo --------------------------------------------------------------------------------------------------
echo
echo tfa2fa.ex01
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_01.fa 
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_01.fa 
echo
echo tfa2fa.ex01 masking several regions with Ns
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_01B.fa -m ./coord_100Kb.txt
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_01B.fa -m ./coord_100Kb.txt
echo
echo tfa2fa.ex02
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_02.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_tfa2fa_02.fa.log.txt
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_02.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_tfa2fa_02.fa.log.txt
echo
echo tfa2fa.ex02B
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_02B.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2fa_02B.fa.log.txt
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_02B.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2fa_02B.fa.log.txt
echo
echo tfa2fa.ex03 should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_03.fa -E ./100Kchr10_tfa2fa_02.fa_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_03.fa -E ./100Kchr10_tfa2fa_02.fa_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo tfa2fa.ex03B should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_03B.fa -E ./100Kchr10_tfa2fa_02B.fa_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F tfasta -f fasta  -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_03B.fa -E ./100Kchr10_tfa2fa_02B.fa_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
#echo tfa2fa.ex06
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_04.fa -W ./coord_100Kb.txt
#echo tfa2fa.ex07
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_05.fa -w 10000 -s 20000
#echo tfa2fa.ex08
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_06.fa -P 0
#echo tfa2fa.ex09
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_07.fa -p 2
#echo tfa2fa.ex10
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_08.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2
#echo tfa2fa.ex11
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_09.fa -E ./100Kchr10_tfa2fa_08.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.gz -p 2
#echo tfa2fa.ex12
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_10.fa -W ./coord_100Kb.txt -p 2
#echo tfa2fa.ex13
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_11.fa -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -W ./coord_100Kb.txt -P 0 
#echo tfa2fa.ex14
#../bin/fastaconvtr -F tfasta -f fasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2fa_12.fa -E ./100Kchr10_tfa2fa_11.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.gz -P 0 -p 2

#TFASTA TO TFASTA
echo --------------------------------------------------------------------------------------------------
echo tfasta to tfasta: Useful for generating weighting file from GFF file
echo --------------------------------------------------------------------------------------------------
echo
echo tfa2tfa.ex01
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa -o ./100Kchr10_tfa2tfa_01.tfa.gz 
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa -o ./100Kchr10_tfa2tfa_01.tfa.gz 
echo
echo tfa2tfa.ex02
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_02.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_tfa2tfa_02.tfa.gz.log.txt
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_02.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 > ./100Kchr10_tfa2tfa_02.tfa.gz.log.txt
echo
echo tfa2tfa.ex02B
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_02B.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2tfa_02B.tfa.gz.log.txt
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_02B.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 0 > ./100Kchr10_tfa2tfa_02B.tfa.gz.log.txt
echo
echo tfa2tfa.ex03 should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_03.tfa.gz -E ./100Kchr10_tfa2tfa_02.tfa.gz_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_03.tfa.gz -E ./100Kchr10_tfa2tfa_02.tfa.gz_npops1_nsam42_nonsynonymous_max_IncludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
echo tfa2tfa.ex03B should give same results than previous
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_03B.tfa.gz -E ./100Kchr10_tfa2tfa_02B.tfa.gz_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_03B.tfa.gz -E ./100Kchr10_tfa2tfa_02B.tfa.gz_npops1_nsam42_nonsynonymous_max_ExcludeMissingVariantsmhits_NOoutg_ploidy1_WEIGHTS.gz
echo
#echo tfa2tfa.ex06
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_04.tfa.gz -W ./coord_100Kb.txt
#echo tfa2tfa.ex07
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_05.tfa.gz -w 10000 -s 20000
#echo tfa2tfa.ex08
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_06.tfa.gz -P 0
#echo tfa2tfa.ex09
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_07.tfa.gz -p 2
#echo tfa2tfa.ex10
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_08.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -p 2
#echo tfa2tfa.ex11
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_09.tfa.gz -E ./100Kchr10_tfa2tfa_08.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.gz -p 2
#echo tfa2tfa.ex12
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_10.tfa.gz -W ./coord_100Kb.txt -p 2
#echo tfa2tfa.ex13
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_01.tfa.gz -g ./100Kchr10.gtf nonsynonymous Nuclear_Universal -c max -u 1 -W ./coord_100Kb.txt -P 0 
#echo tfa2tfa.ex14
#../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_12.tfa.gz -E ./100Kchr10_tfa2tfa_11.tfa.gz_nonsynonymous_max_IncludeMissing_NOoutg_ploidy1_WEIGHTS.gz -P 0 -p 2

#GZ INPUT & GZ OUTPUT
echo --------------------------------------------------------------------------------------------------
echo tfasta to tfasta: Using GZ files as inputs as and outputs
echo --------------------------------------------------------------------------------------------------
echo
echo tfa2tfa.ex01 with compressed data
echo ../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_01_2.tfa.gz
../bin/fastaconvtr -F tfasta -f tfasta -i ./100Kchr10.tfa.gz -o ./100Kchr10_tfa2tfa_01_2.tfa.gz
echo
echo gunzip ./100Kchr10_tfa2tfa_01_2.tfa.gz
gunzip ./100Kchr10_tfa2tfa_01_2.tfa.gz
echo
echo diff ./100Kchr10_tfa2tfa_01.tfa ./100Kchr10_tfa2tfa_01_2.tfa
diff ./100Kchr10_tfa2tfa_01.tfa ./100Kchr10_tfa2tfa_01_2.tfa


