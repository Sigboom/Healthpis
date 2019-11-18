CC=g++
boostlib=-lboost_regex
CFLAGS=-g -Wall -std=c++11 $(boostlib)

LIBSPATH=../lib/
SigToolkit=../sigToolkit/build/

Target=Sigpital_manager
MAINCPP=Sigpital.cpp

LIBS=${wildcard $(LIBSPATH)*.so}

.PHONY: clean

$(Target): SigToolkit $(MAINCPP)
	$(CC) $(CFLAGS) -o $(Target) $(MAINCPP) $(LIBS)

SigToolkit:
	@cd $(SigToolkit); make;

clean:
	rm -f $(OBJS) $(Target)
