# for include Makefile.inc

include ../Makefile.inc

${TLPI_LIB} : *.cpp ename.c.inc
	${CC} -c ${CCFLAGS} *.cpp
	${RM} ${TLPI_LIB}
	${AR} rs ${TLPI_LIB} *.o

ename.c.inc:
	sh Build_ename.sh > ename.c.inc
	echo 1>&2 "ename.c.inc build"

clean :
	${RM} *.o ${TLPI_LIB} ename.c.inc

