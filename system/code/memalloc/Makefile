# include Makefile.inc
#

include ../Makefile.inc

all : sbrk ${MALLOC_LIB} test

sbrk : sbrk.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

${MALLOC_LIB} : malloc.cpp
	${CC} -c ${CCFLAGS} ${OPT_DEBUG} -o malloc.o $<
	${RM} $@
	${AR} rs $@ malloc.o

test : test.cpp
	${CC} ${CCFLAGS} ${INC_MALLOC} ${OPT_DEBUG} -o $@ $< ${MALLOC_LIB}

.PHONY : clean
clean:
	${RM} sbrk malloc.o ${MALLOC_LIB} test

