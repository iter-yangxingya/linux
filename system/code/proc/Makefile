# include Makefile.inc
#

include ../Makefile.inc

all : environ

environ : environ.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

.PHONY : clean
clean:
	${RM} environ
