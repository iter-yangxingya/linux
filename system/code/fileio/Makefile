# include Makefile.inc
#

include ../Makefile.inc

all : copy min_fd seek_io tee copy_ex bad_open mt_append fstat copy_fd offset_rw \
	readv temp_file append atomic_append dup rwv

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

bad_open : bad_exclude_open.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

mt_append : mt_append.cpp
	${CC} ${CCFLAGS} ${THREAD_FLAGS} -o $@ $< ${TLPI_LIB}

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

append : append.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

atomic_append : atomic_append.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

dup : dup.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

rwv : readv_writev.cpp
	${CC} ${CCFLAGS} -o $@ $< ${TLPI_LIB}

.PHONY : clean
clean:
	${RM} copy min_fd seek_io tee copy_ex bad_open mt_append fstat copy_fd \
	offset_rw readv temp_file append atomic_append dup rwv
