CC=g++
boostlib=-lboost_regex
DEBUGKEY=SIG_
DEBUG=FALSE
CFLAGS=-g -Wall -std=c++11 -D$(DEBUG)

LIBSPATH=../../lib/
DOCTORPATH=../src/doctors/
MANAGERPATH=../src/
SigToolkit=../../sigToolkit/build/

Target=Sigpital_manager
MAINCPP=Sigpital.cpp
OBJS=doctor.o manager.o

LIBS=${wildcard $(LIBSPATH)*.so}

.PHONY: clean

ifneq ($(findstring $(DEBUGKEY),$(DEBUG)),)
all: SigToolkit $(OBJS) $(MAINCPP)
	$(CC) $(CFLAGS) $(boostlib) -o $(Target) $(MAINCPP) $(OBJS) $(LIBS)
else
all: $(MAINCPP)
	$(CC) $(CFLAGS) -o $(Target) $(MAINCPP)
endif

manager.o: $(MANAGERPATH)manager.cpp
	$(CC) $(CFLAGS) -c -o manager.o $(MANAGERPATH)manager.cpp

doctor.o: $(DOCTORPATH)serverDoctor.cpp
	$(CC) $(CFLAGS) -c -o doctor.o $(DOCTORPATH)serverDoctor.cpp

SigToolkit:
	@cd $(SigToolkit); make DEBUG=$(DEBUG);

clean:
	rm -f $(OBJS) $(Target)
	@cd $(SigToolkit); make clean;

