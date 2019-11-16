CC=g++
CFLAGS=-g -Wall -std=c++11

LIBPATH=../../lib/
SRCPATH=../src/

Target=libsigToolkit.so
ExceOBJS=confException.o serverException.o
OBJS=baseTools.o sigNet.o mediCentre.o doctor.o $(ExceOBJS)

.PHONY: clean

all: $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIBPATH)$(Target) $(OBJS)

baseTools.o: $(SRCPATH)baseTools.cpp
	$(CC) $(CFLAGS) -c -o baseTools.o $(SRCPATH)baseTools.cpp

sigNet.o: $(SRCPATH)sigNet.cpp
	$(CC) $(CFLAGS) -c -o sigNet.o $(SRCPATH)sigNet.cpp

confException.o: $(SRCPATH)confException.cpp
	$(CC) $(CFLAGS) -c -o confException.o $(SRCPATH)confException.cpp

serverException.o: $(SRCPATH)serverException.cpp
	$(CC) $(CFLAGS) -c -o serverException.o $(SRCPATH)serverException.cpp

doctor.o: $(SRCPATH)doctor.cpp
	$(CC) $(CFLAGS) -c -o doctor.o $(SRCPATH)doctor.cpp

mediCentre.o: $(SRCPATH)mediCentre.cpp
	$(CC) $(CFLAGS) -c -o mediCentre.o $(SRCPATH)mediCentre.cpp

clean:
	rm -f $(OBJS)

