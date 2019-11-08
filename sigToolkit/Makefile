CC=g++
CFLAGS=-g -Wall -std=c++11

LIBPATH=../../lib/

Target=libsigToolkit.so
ExceOBJS=confException.o
OBJS=baseTools.o sigNet.o mediCentre.o $(ExceOBJS)

.PHONY: clean

all: $(OBJS)
	cd build && if [ -f $(LIBPATH) ]; then mkdir $(LIBPATH); fi
	cd build && $(CC) $(CFLAGS) -shared -fPIC -o $(LIBPATH)$(Target) $(OBJS)

baseTools.o: src/baseTools.cpp
	cd build && $(CC) $(CFLAGS) -c -o baseTools.o ../src/baseTools.cpp

sigNet.o: src/sigNet.cpp
	cd build && $(CC) $(CFLAGS) -c -o sigNet.o ../src/sigNet.cpp

confException.o: src/confException.cpp
	cd build && $(CC) $(CFLAGS) -c -o confException.o ../src/confException.cpp

mediCentre.o: src/mediCentre.cpp
	cd build && $(CC) $(CFLAGS) -c -o mediCentre.o ../src/mediCentre.cpp

clean:
	cd build && rm -f $(OBJS)

