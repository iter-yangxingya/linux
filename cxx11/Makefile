
# for compile new_feature.cpp Makefile.

all: new_feature

CC=g++
# complie options:
CPPFLAGS=-std=c++11
# link options:
LDFLAGS=-pthread

# start compile and link.

# link to binary file.
new_feature:new_feature.o
	$(CC) $(LDFLAGS) -o $@ $^

# compile to object file.
new_feature.o:new_feature.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm new_feature.o new_feature

