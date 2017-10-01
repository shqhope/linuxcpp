APPNAME=test1

APPENDFILES=$(wildcard ../basestruct/*.cpp)
FILES=main.cpp $(wildcard src/*.cpp) $(APPENDFILES)

#$(warning $(FILES))

DFILES=$(FILES:.cpp=.d)

ROBJS=$(FILES:.cpp=.o)

DBGOBJS=$(FILES:.cpp=.dbg.o)

HEADS=$(APPENDFILES:.cpp=.h) ../basestruct/heads.h

Debug:$(HEADS)
Debug:$(DBGOBJS)
Debug:$(APPNAME)d

$(APPNAME)d:
	g++ -o $(APPNAME)d -g $(DBGOBJS)

$(DBGOBJS):%.dbg.o:%.cpp
	g++ -o $@ -g -c $<

clean:
	rm -rf *.dbg.o *.o $(APPNAME) $(APPNAME)d $(DBGOBJS)
