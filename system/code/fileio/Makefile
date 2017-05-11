# include Makefile.inc
#

include ../Makefile.inc

all : copy min_fd seek_io tee copy_ex fstat copy_fd offset_rw readv temp_file

copy : copy.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

min_fd : min_fd.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

seek_io : seek_io.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

tee : tee.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

copy_ex : copy_ex.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

fstat : fstat.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

copy_fd : copy_fd.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

offset_rw : spec_off_rw.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

readv : t_readv.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

temp_file : temp_file.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

.PHONY : clean
clean:
	${RM} copy min_fd seek_io tee copy_ex fstat copy_fd offset_rw readv temp_file
