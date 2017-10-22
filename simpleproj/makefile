APPNAME=test1

BASESTRUCTFILES=$(wildcard ../basestruct/*.cpp)
APUEFILES=$(wildcard ../APUE/*.cpp)
ZWFILES=$(wildcard ../ZW/basefun/*.cpp)
FILES=main.cpp $(wildcard src/*.cpp) $(BASESTRUCTFILES) $(ZWFILES)


#$(warning $(FILES))

DFILES=$(FILES:.cpp=.d)

ROBJS=$(FILES:.cpp=.o)

DBGOBJS=$(FILES:.cpp=.dbg.o)

HEADS=$(BASESTRUCTFILES:.cpp=.h) ../basestruct/heads.h

Debug:$(HEADS)
Debug:$(DBGOBJS)
Debug:$(APPNAME)d

$(APPNAME)d:
	g++ -o $(APPNAME)d -g $(DBGOBJS) -lpthread

$(DBGOBJS):%.dbg.o:%.cpp
	g++ -o $@ -g -c $<

clean:
	rm -rf *.dbg.o *.o $(APPNAME) $(APPNAME)d $(DBGOBJS)
