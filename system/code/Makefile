# build all sub-directory files.
#

DIRS = lib \
	   fileio \
	   proc

all :
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}); done

.PHONY : clean
clean:
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean); done

