CC=g++
CFLAGS=-g -Wall -std=c++11

LIBSPATH=../../lib/
SigToolkit=../sigToolkit/

Target=Sigpital_manager
MAINCPP=Sigpital.cpp

#exist = $(shell if [ -f $(LIBSPATH) ]; then echo "exist"; else echo "notexist"; fi;)
#ifeq(exist, "notexist")
#	mkdir $(LIBSPATH);
#endif
LIBS=${wildcard $(LIBSPATH)*.so}

.PHONY: clean

$(Target): SigToolkit $(MAINCPP)
	$(CC) $(CFLAGS) -o $(Target) $(MAINCPP) $(LIBS)

SigToolkit:
	@cd $(SigToolkit); make;

clean:
	rm -f $(OBJS) $(Target)
