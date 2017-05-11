# this makefile for compile file.
#

CC=g++
CCFLAGS=-c
LDFLAGS=

glibc_version:glibc_version.o
	$(CC) $(LDFLAGS) -o $@ $<

glibc_version.o:glibc_version.cpp
	$(CC) $(CCFLAGS) -o $@ $<

.PHONY:clean

clean:
	rm glibc_version.o glibc_version
