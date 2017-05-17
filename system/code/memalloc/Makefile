# include Makefile.inc
#

include ../Makefile.inc

all : sbrk libmalloc.a

sbrk : sbrk.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

libmalloc.a : malloc.cpp
	${CC} -c ${CCFLAGS} -o malloc.o $<
	${RM} $@
	${AR} rs $@ malloc.o

.PHONY : clean
clean:
	${RM} sbrk malloc.o libmalloc.a

