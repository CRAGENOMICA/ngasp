#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/bam.o \
	${OBJECTDIR}/bam2bcf.o \
	${OBJECTDIR}/bam2bcf_indel.o \
	${OBJECTDIR}/bam2depth.o \
	${OBJECTDIR}/bam_addrprg.o \
	${OBJECTDIR}/bam_aux.o \
	${OBJECTDIR}/bam_cat.o \
	${OBJECTDIR}/bam_color.o \
	${OBJECTDIR}/bam_flags.o \
	${OBJECTDIR}/bam_import.o \
	${OBJECTDIR}/bam_index.o \
	${OBJECTDIR}/bam_lpileup.o \
	${OBJECTDIR}/bam_mate.o \
	${OBJECTDIR}/bam_md.o \
	${OBJECTDIR}/bam_plbuf.o \
	${OBJECTDIR}/bam_plcmd.o \
	${OBJECTDIR}/bam_quickcheck.o \
	${OBJECTDIR}/bam_reheader.o \
	${OBJECTDIR}/bam_rmdup.o \
	${OBJECTDIR}/bam_rmdupse.o \
	${OBJECTDIR}/bam_sort.o \
	${OBJECTDIR}/bam_split.o \
	${OBJECTDIR}/bam_stat.o \
	${OBJECTDIR}/bam_tview.o \
	${OBJECTDIR}/bam_tview_curses.o \
	${OBJECTDIR}/bam_tview_html.o \
	${OBJECTDIR}/bamshuf.o \
	${OBJECTDIR}/bamtk.o \
	${OBJECTDIR}/bedcov.o \
	${OBJECTDIR}/bedidx.o \
	${OBJECTDIR}/cut_target.o \
	${OBJECTDIR}/dict.o \
	${OBJECTDIR}/errmod.o \
	${OBJECTDIR}/faidx.o \
	${OBJECTDIR}/htslib-1.3.1/bgzf.o \
	${OBJECTDIR}/htslib-1.3.1/bgzip.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_codecs.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_decode.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_encode.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_external.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_index.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_io.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_samtools.o \
	${OBJECTDIR}/htslib-1.3.1/cram/cram_stats.o \
	${OBJECTDIR}/htslib-1.3.1/cram/files.o \
	${OBJECTDIR}/htslib-1.3.1/cram/mFILE.o \
	${OBJECTDIR}/htslib-1.3.1/cram/open_trace_file.o \
	${OBJECTDIR}/htslib-1.3.1/cram/pooled_alloc.o \
	${OBJECTDIR}/htslib-1.3.1/cram/rANS_static.o \
	${OBJECTDIR}/htslib-1.3.1/cram/sam_header.o \
	${OBJECTDIR}/htslib-1.3.1/cram/string_alloc.o \
	${OBJECTDIR}/htslib-1.3.1/cram/thread_pool.o \
	${OBJECTDIR}/htslib-1.3.1/cram/vlen.o \
	${OBJECTDIR}/htslib-1.3.1/cram/zfio.o \
	${OBJECTDIR}/htslib-1.3.1/faidx.o \
	${OBJECTDIR}/htslib-1.3.1/hfile.o \
	${OBJECTDIR}/htslib-1.3.1/hfile_net.o \
	${OBJECTDIR}/htslib-1.3.1/hts.o \
	${OBJECTDIR}/htslib-1.3.1/htsfile.o \
	${OBJECTDIR}/htslib-1.3.1/kfunc.o \
	${OBJECTDIR}/htslib-1.3.1/knetfile.o \
	${OBJECTDIR}/htslib-1.3.1/kstring.o \
	${OBJECTDIR}/htslib-1.3.1/md5.o \
	${OBJECTDIR}/htslib-1.3.1/plugin.o \
	${OBJECTDIR}/htslib-1.3.1/regidx.o \
	${OBJECTDIR}/htslib-1.3.1/sam.o \
	${OBJECTDIR}/htslib-1.3.1/synced_bcf_reader.o \
	${OBJECTDIR}/htslib-1.3.1/tabix.o \
	${OBJECTDIR}/htslib-1.3.1/tbx.o \
	${OBJECTDIR}/htslib-1.3.1/vcf.o \
	${OBJECTDIR}/htslib-1.3.1/vcf_sweep.o \
	${OBJECTDIR}/htslib-1.3.1/vcfutils.o \
	${OBJECTDIR}/kprobaln.o \
	${OBJECTDIR}/padding.o \
	${OBJECTDIR}/phase.o \
	${OBJECTDIR}/sam.o \
	${OBJECTDIR}/sam_header.o \
	${OBJECTDIR}/sam_opts.o \
	${OBJECTDIR}/sam_view.o \
	${OBJECTDIR}/sample.o \
	${OBJECTDIR}/stats.o \
	${OBJECTDIR}/stats_isize.o


# C Compiler Flags
CFLAGS=-Wall -O2 -g -I. -Ihtslib-1.3.1

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsamtoolslib.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsamtoolslib.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsamtoolslib.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsamtoolslib.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsamtoolslib.a

${OBJECTDIR}/bam.o: bam.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam.o bam.c

${OBJECTDIR}/bam2bcf.o: bam2bcf.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam2bcf.o bam2bcf.c

${OBJECTDIR}/bam2bcf_indel.o: bam2bcf_indel.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam2bcf_indel.o bam2bcf_indel.c

${OBJECTDIR}/bam2depth.o: bam2depth.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam2depth.o bam2depth.c

${OBJECTDIR}/bam_addrprg.o: bam_addrprg.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_addrprg.o bam_addrprg.c

${OBJECTDIR}/bam_aux.o: bam_aux.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_aux.o bam_aux.c

${OBJECTDIR}/bam_cat.o: bam_cat.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_cat.o bam_cat.c

${OBJECTDIR}/bam_color.o: bam_color.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_color.o bam_color.c

${OBJECTDIR}/bam_flags.o: bam_flags.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_flags.o bam_flags.c

${OBJECTDIR}/bam_import.o: bam_import.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_import.o bam_import.c

${OBJECTDIR}/bam_index.o: bam_index.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_index.o bam_index.c

${OBJECTDIR}/bam_lpileup.o: bam_lpileup.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_lpileup.o bam_lpileup.c

${OBJECTDIR}/bam_mate.o: bam_mate.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_mate.o bam_mate.c

${OBJECTDIR}/bam_md.o: bam_md.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_md.o bam_md.c

${OBJECTDIR}/bam_plbuf.o: bam_plbuf.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_plbuf.o bam_plbuf.c

${OBJECTDIR}/bam_plcmd.o: bam_plcmd.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_plcmd.o bam_plcmd.c

${OBJECTDIR}/bam_quickcheck.o: bam_quickcheck.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_quickcheck.o bam_quickcheck.c

${OBJECTDIR}/bam_reheader.o: bam_reheader.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_reheader.o bam_reheader.c

${OBJECTDIR}/bam_rmdup.o: bam_rmdup.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_rmdup.o bam_rmdup.c

${OBJECTDIR}/bam_rmdupse.o: bam_rmdupse.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_rmdupse.o bam_rmdupse.c

${OBJECTDIR}/bam_sort.o: bam_sort.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_sort.o bam_sort.c

${OBJECTDIR}/bam_split.o: bam_split.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_split.o bam_split.c

${OBJECTDIR}/bam_stat.o: bam_stat.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_stat.o bam_stat.c

${OBJECTDIR}/bam_tview.o: bam_tview.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_tview.o bam_tview.c

${OBJECTDIR}/bam_tview_curses.o: bam_tview_curses.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_tview_curses.o bam_tview_curses.c

${OBJECTDIR}/bam_tview_html.o: bam_tview_html.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bam_tview_html.o bam_tview_html.c

${OBJECTDIR}/bamshuf.o: bamshuf.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bamshuf.o bamshuf.c

${OBJECTDIR}/bamtk.o: bamtk.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bamtk.o bamtk.c

${OBJECTDIR}/bedcov.o: bedcov.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bedcov.o bedcov.c

${OBJECTDIR}/bedidx.o: bedidx.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bedidx.o bedidx.c

${OBJECTDIR}/cut_target.o: cut_target.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cut_target.o cut_target.c

${OBJECTDIR}/dict.o: dict.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dict.o dict.c

${OBJECTDIR}/errmod.o: errmod.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/errmod.o errmod.c

${OBJECTDIR}/faidx.o: faidx.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/faidx.o faidx.c

${OBJECTDIR}/htslib-1.3.1/bgzf.o: htslib-1.3.1/bgzf.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/bgzf.o htslib-1.3.1/bgzf.c

${OBJECTDIR}/htslib-1.3.1/bgzip.o: htslib-1.3.1/bgzip.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/bgzip.o htslib-1.3.1/bgzip.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_codecs.o: htslib-1.3.1/cram/cram_codecs.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_codecs.o htslib-1.3.1/cram/cram_codecs.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_decode.o: htslib-1.3.1/cram/cram_decode.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_decode.o htslib-1.3.1/cram/cram_decode.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_encode.o: htslib-1.3.1/cram/cram_encode.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_encode.o htslib-1.3.1/cram/cram_encode.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_external.o: htslib-1.3.1/cram/cram_external.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_external.o htslib-1.3.1/cram/cram_external.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_index.o: htslib-1.3.1/cram/cram_index.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_index.o htslib-1.3.1/cram/cram_index.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_io.o: htslib-1.3.1/cram/cram_io.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_io.o htslib-1.3.1/cram/cram_io.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_samtools.o: htslib-1.3.1/cram/cram_samtools.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_samtools.o htslib-1.3.1/cram/cram_samtools.c

${OBJECTDIR}/htslib-1.3.1/cram/cram_stats.o: htslib-1.3.1/cram/cram_stats.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/cram_stats.o htslib-1.3.1/cram/cram_stats.c

${OBJECTDIR}/htslib-1.3.1/cram/files.o: htslib-1.3.1/cram/files.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/files.o htslib-1.3.1/cram/files.c

${OBJECTDIR}/htslib-1.3.1/cram/mFILE.o: htslib-1.3.1/cram/mFILE.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/mFILE.o htslib-1.3.1/cram/mFILE.c

${OBJECTDIR}/htslib-1.3.1/cram/open_trace_file.o: htslib-1.3.1/cram/open_trace_file.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/open_trace_file.o htslib-1.3.1/cram/open_trace_file.c

${OBJECTDIR}/htslib-1.3.1/cram/pooled_alloc.o: htslib-1.3.1/cram/pooled_alloc.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/pooled_alloc.o htslib-1.3.1/cram/pooled_alloc.c

${OBJECTDIR}/htslib-1.3.1/cram/rANS_static.o: htslib-1.3.1/cram/rANS_static.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/rANS_static.o htslib-1.3.1/cram/rANS_static.c

${OBJECTDIR}/htslib-1.3.1/cram/sam_header.o: htslib-1.3.1/cram/sam_header.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/sam_header.o htslib-1.3.1/cram/sam_header.c

${OBJECTDIR}/htslib-1.3.1/cram/string_alloc.o: htslib-1.3.1/cram/string_alloc.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/string_alloc.o htslib-1.3.1/cram/string_alloc.c

${OBJECTDIR}/htslib-1.3.1/cram/thread_pool.o: htslib-1.3.1/cram/thread_pool.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/thread_pool.o htslib-1.3.1/cram/thread_pool.c

${OBJECTDIR}/htslib-1.3.1/cram/vlen.o: htslib-1.3.1/cram/vlen.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/vlen.o htslib-1.3.1/cram/vlen.c

${OBJECTDIR}/htslib-1.3.1/cram/zfio.o: htslib-1.3.1/cram/zfio.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1/cram
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/cram/zfio.o htslib-1.3.1/cram/zfio.c

${OBJECTDIR}/htslib-1.3.1/faidx.o: htslib-1.3.1/faidx.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/faidx.o htslib-1.3.1/faidx.c

${OBJECTDIR}/htslib-1.3.1/hfile.o: htslib-1.3.1/hfile.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/hfile.o htslib-1.3.1/hfile.c

${OBJECTDIR}/htslib-1.3.1/hfile_net.o: htslib-1.3.1/hfile_net.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/hfile_net.o htslib-1.3.1/hfile_net.c

${OBJECTDIR}/htslib-1.3.1/hts.o: htslib-1.3.1/hts.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/hts.o htslib-1.3.1/hts.c

${OBJECTDIR}/htslib-1.3.1/htsfile.o: htslib-1.3.1/htsfile.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/htsfile.o htslib-1.3.1/htsfile.c

${OBJECTDIR}/htslib-1.3.1/kfunc.o: htslib-1.3.1/kfunc.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/kfunc.o htslib-1.3.1/kfunc.c

${OBJECTDIR}/htslib-1.3.1/knetfile.o: htslib-1.3.1/knetfile.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/knetfile.o htslib-1.3.1/knetfile.c

${OBJECTDIR}/htslib-1.3.1/kstring.o: htslib-1.3.1/kstring.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/kstring.o htslib-1.3.1/kstring.c

${OBJECTDIR}/htslib-1.3.1/md5.o: htslib-1.3.1/md5.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/md5.o htslib-1.3.1/md5.c

${OBJECTDIR}/htslib-1.3.1/plugin.o: htslib-1.3.1/plugin.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/plugin.o htslib-1.3.1/plugin.c

${OBJECTDIR}/htslib-1.3.1/regidx.o: htslib-1.3.1/regidx.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/regidx.o htslib-1.3.1/regidx.c

${OBJECTDIR}/htslib-1.3.1/sam.o: htslib-1.3.1/sam.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/sam.o htslib-1.3.1/sam.c

${OBJECTDIR}/htslib-1.3.1/synced_bcf_reader.o: htslib-1.3.1/synced_bcf_reader.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/synced_bcf_reader.o htslib-1.3.1/synced_bcf_reader.c

${OBJECTDIR}/htslib-1.3.1/tabix.o: htslib-1.3.1/tabix.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/tabix.o htslib-1.3.1/tabix.c

${OBJECTDIR}/htslib-1.3.1/tbx.o: htslib-1.3.1/tbx.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/tbx.o htslib-1.3.1/tbx.c

${OBJECTDIR}/htslib-1.3.1/vcf.o: htslib-1.3.1/vcf.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/vcf.o htslib-1.3.1/vcf.c

${OBJECTDIR}/htslib-1.3.1/vcf_sweep.o: htslib-1.3.1/vcf_sweep.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/vcf_sweep.o htslib-1.3.1/vcf_sweep.c

${OBJECTDIR}/htslib-1.3.1/vcfutils.o: htslib-1.3.1/vcfutils.c
	${MKDIR} -p ${OBJECTDIR}/htslib-1.3.1
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/htslib-1.3.1/vcfutils.o htslib-1.3.1/vcfutils.c

${OBJECTDIR}/kprobaln.o: kprobaln.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kprobaln.o kprobaln.c

${OBJECTDIR}/padding.o: padding.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/padding.o padding.c

${OBJECTDIR}/phase.o: phase.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/phase.o phase.c

${OBJECTDIR}/sam.o: sam.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sam.o sam.c

${OBJECTDIR}/sam_header.o: sam_header.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sam_header.o sam_header.c

${OBJECTDIR}/sam_opts.o: sam_opts.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sam_opts.o sam_opts.c

${OBJECTDIR}/sam_view.o: sam_view.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sam_view.o sam_view.c

${OBJECTDIR}/sample.o: sample.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sample.o sample.c

${OBJECTDIR}/stats.o: stats.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stats.o stats.c

${OBJECTDIR}/stats_isize.o: stats_isize.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stats_isize.o stats_isize.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
