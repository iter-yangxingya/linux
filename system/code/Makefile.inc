# Makefile.inc for all sub-directory include.

O_DIR=..
INC_DIR=${O_DIR}/lib
LIB_DIR=${O_DIR}
TLPI_LIB=${O_DIR}/libtlpi.a

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

THREAD_FLAGS = -pthread
LDFLAGS = ${TLPI_LIB} -lm

LKFLAGS = -L${O_DIR}

RM = rm -f
