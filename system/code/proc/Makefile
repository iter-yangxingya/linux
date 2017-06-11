# include Makefile.inc
#

include ../Makefile.inc

all : mem_segment link_argv show_env modify_env longjmp jmp_vars jmp_vars_o \
	jmp_return environ

mem_segment : mem_segment.cpp
	${CC} ${CCFLAGS_NOWARN} -o $@ $< ${TLPI_LIB}

link_argv : link_argv0.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}
	ln -s $@ newbi

show_env : show_env.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

modify_env : modify_env.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

longjmp : longjmp.cpp
	${CC} ${CCFLAGS_NOWARN} -o $@ $< ${TLPI_LIB}

jmp_vars : jmp_vars.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

jmp_vars_o : jmp_vars.cpp
	${CC} ${CCFLAGS} -O -o $@ $< ${TLPI_LIB}

jmp_return : jmp_return.cpp
	${CC} ${CCFLAGS} -O -o $@ $< ${TLPI_LIB}

environ : environ.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

.PHONY : clean
clean:
	${RM} mem_segment link_argv show_env modify_env longjmp jmp_vars jmp_vars_o \
	jmp_return environ
	${RM} newbi

