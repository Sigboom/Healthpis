CC=g++
CFLAGS=-g -Wall -std=c++11


LIBSPATH=../../lib/
SigToolkit=../../sigToolkit/build/
MAINCPP=main.cpp

Target=server

LIBS=${wildcard $(LIBSPATH)*.so}


.PHONY: clean

$(Target): SigToolkits $(MAINCPP)
	$(CC) $(CFLAGS) -o $(Target) $(MAINCPP) $(LIBS)

SigToolkits:
	@cd $(SigToolkit); make;

clean:
	rm -f $(OBJS) $(Target)

