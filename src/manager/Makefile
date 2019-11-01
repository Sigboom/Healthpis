CC=g++

CFLAGS=-g -Wall -std=c++11

OBJS=baseTools.o manager.o sigNet.o

SigToolkit=../sigToolkit/
Include=../include/

.PHONY: clean

manager: $(OBJS)
	$(CC) $(CFLAGS) -o manager $(OBJS)

baseTools.o: $(SigToolkit)baseTools.cpp $(Include)baseTools.h
	$(CC) $(CFLAGS) -c -o baseTools.o $(SigToolkit)baseTools.cpp

sigNet.o: $(SigToolkit)sigNet.cpp $(Include)sigNet.h
	$(CC) $(CFLAGS) -c -o sigNet.o $(SigToolkit)sigNet.cpp

manager.o: manager.cpp
	$(CC) $(CFLAGS) -c -o manager.o manager.cpp

clean:
	rm -f $(OBJS) manager
