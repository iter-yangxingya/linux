# include Makefile.inc
#

include ../Makefile.inc

all : sbrk

sbrk : sbrk.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

.PHONY : clean
clean:
	${RM} sbrk

