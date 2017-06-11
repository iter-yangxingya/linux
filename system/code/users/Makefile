# include Makefile.inc
#

include ../Makefile.inc

all : user ${UG_LOOKUP_LIB} scan_user

user : user.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

${UG_LOOKUP_LIB} : ug_lookup.cpp
	${CC} -c ${CCFLAGS} ${OPT_DEBUG} -o ug_lookup.o $<
	${RM} $@
	${AR} rs $@ ug_lookup.o

scan_user : scan_user.cpp
	${CC} ${CCFLAGS} -o $@ $<

.PHONY : clean
clean:
	${RM} user ug_lookup.o ${UG_LOOKUP_LIB} scan_user

