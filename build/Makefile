CC=g++
CFLAGS=-g -Wall -std=c++11

.PHONY: clean

all: Sigpital_manager Sigpital_server

Sigpital_manager: ../src/manager/Sigpital.cpp
	cd ../src/manager/ && make;

Sigpital_server:

clean:
	rm -f Sigpital_*
