CC=g++

CFLAGS=-g -Wall

OBJS=baseTools.o server.o sigNet.o

SigToolkit=../sigToolkit/
Include=../include/

.PHONY: clean

server: $(OBJS)
	$(CC) $(CFLAGS) -o server $(OBJS)

baseTools.o: $(SigToolkit)baseTools.cpp $(Include)baseTools.h
	$(CC) $(CFLAGS) -c -o baseTools.o $(SigToolkit)baseTools.cpp

sigNet.o: $(SigToolkit)sigNet.cpp $(Include)sigNet.h
	$(CC) $(CFLAGS) -c -o sigNet.o $(SigToolkit)sigNet.cpp

server.o: server.cpp
	$(CC) $(CFLAGS) -c -o server.o server.cpp

clean:
	rm -f $(OBJS) server 
