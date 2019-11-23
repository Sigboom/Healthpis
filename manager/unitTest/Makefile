CC=g++
boostlib=-lboost_regex
DEBUG=NODEBUG
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

$(Target): SigToolkit $(OBJS) $(MAINCPP)
	$(CC) $(CFLAGS) $(boostlib) -o $(Target) $(MAINCPP) $(OBJS) $(LIBS)

manager.o: $(MANAGERPATH)manager.cpp
	$(CC) $(CFLAGS) -c -o manager.o $(MANAGERPATH)manager.cpp

doctor.o: $(DOCTORPATH)serverDoctor.cpp
	$(CC) $(CFLAGS) -c -o doctor.o $(DOCTORPATH)serverDoctor.cpp

SigToolkit:
	@cd $(SigToolkit); make DEBUG=$(DEBUG);

clean:
	rm -f $(OBJS) $(Target)
	@cd $(SigToolkit); make clean;

