CC=g++
DEBUG=NODEBUG
CFLAGS=-g -Wall -std=c++11 -D$(DEBUG)

LIBPATH=../../lib/
SRCPATH=../src/

Target=libsigToolkit.so
ExceOBJS=confException.o serverException.o doctorException.o
OBJS=baseTools.o sigNet.o mediCentre.o doctor.o $(ExceOBJS)

.PHONY: clean

all: $(OBJS)
	if [ ! -d $(LIBPATH) ]; then mkdir $(LIBPATH); fi
	$(CC) $(CFLAGS) -shared -fPIC -o $(LIBPATH)$(Target) $(OBJS)

baseTools.o: $(SRCPATH)baseTools.cpp
	$(CC) $(CFLAGS) -c -o baseTools.o $(SRCPATH)baseTools.cpp

sigNet.o: $(SRCPATH)sigNet.cpp
	$(CC) $(CFLAGS) -c -o sigNet.o $(SRCPATH)sigNet.cpp

confException.o: $(SRCPATH)confException.cpp
	$(CC) $(CFLAGS) -c -o confException.o $(SRCPATH)confException.cpp

doctorException.o: $(SRCPATH)doctorException.cpp
	$(CC) $(CFLAGS) -c -o doctorException.o $(SRCPATH)doctorException.cpp

serverException.o: $(SRCPATH)serverException.cpp
	$(CC) $(CFLAGS) -c -o serverException.o $(SRCPATH)serverException.cpp

doctor.o: $(SRCPATH)doctor.cpp
	$(CC) $(CFLAGS) -c -o doctor.o $(SRCPATH)doctor.cpp

mediCentre.o: $(SRCPATH)mediCentre.cpp
	$(CC) $(CFLAGS) -c -o mediCentre.o $(SRCPATH)mediCentre.cpp

clean:
	rm -f $(OBJS)

