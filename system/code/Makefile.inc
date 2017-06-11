# Makefile.inc for all sub-directory include.

O_DIR=..
INC_DIR=${O_DIR}/lib
MALLOC_DIR=${O_DIR}/memalloc
UG_LOOKUP_DIR=${O_DIR}/users

LIB_DIR=${O_DIR}
TLPI_LIB=${O_DIR}/libtlpi.a
MALLOC_LIB=${O_DIR}/libmalloc.a
UG_LOOKUP_LIB=${O_DIR}/libug_lookup.a

LINK_LIBRT=lrt
LINK_LIBDL=ldl
LINK_LIBACL=lacl
LINK_LIBCRYPT=lcrypt
LINK_LIBCAP=lcap

CC = g++
CCFLAGS = -std=c++11 \
        -g -I${INC_DIR} \
        -Wall \
        -W

CCFLAGS_NOWARN = -std=c++11 \
        -g -I${INC_DIR}

W_NO_INITIALIZE = -Wunused-but-set-variable
W_UNUSED_PARAMETER = -Wunused-parameter

# for gdb debug info.
OPT_DEBUG = -gstabs+
# for gprof check.
OPT_GPROF = -pg
# for Pre process, only replace MACRO
OPT_EPROC = -E

THREAD_FLAGS = -pthread
INC_MALLOC = -I${MALLOC_DIR}
LDFLAGS = ${TLPI_LIB} -lm

LKFLAGS = -L${O_DIR}

RM = rm -f
