CC=g++
CFLAGS=-g -Wall -std=c++11

LIBPATH=../../lib/

Target=libsigToolkit.so
ExceOBJS=confException.o
OBJS=baseTools.o sigNet.o $(ExceOBJS)


.PHONY: clean

all: $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIBPATH)$(Target) $(OBJS)

baseTools.o: baseTools.cpp
	$(CC) $(CFLAGS) -c -o baseTools.o baseTools.cpp

sigNet.o: sigNet.cpp
	$(CC) $(CFLAGS) -c -o sigNet.o sigNet.cpp

confException.o: confException.cpp
	$(CC) $(CFLAGS) -c -o confException.o confException.cpp

clean:
	rm -f $(OBJS)

