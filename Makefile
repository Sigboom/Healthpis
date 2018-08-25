CC=gcc

CFLAGS = -g -Wall

HEPSOBJS=master.o

.PHONY: clean

master:$(HEPSOBJS)
	$(CC) $(CFLAGS) -o master $(HEPSOBJS)

master.o:master.c master.h
	$(CC) $(CFLAGS) -c -o master.o master.c

sendFile:sendFile.c
	$(CC) $(CFLAGS) -o sendFile sendFile.c

recvFile:recvFile.c
	$(CC) $(CFLAGS) -o recvFile recvFile.c

clean:
	rm -f $(HEPSOBJS) master
