APPNAME=test1

BASESTRUCTFILES=$(wildcard ../basestruct/*.cpp)
APUEFILES=$(wildcard ../apue/*.cpp)
ZWFILES=$(wildcard ../zw/basefun/*.cpp)
FILES0=main.cpp $(wildcard src/*.cpp) $(BASESTRUCTFILES) $(ZWFILES)
#这里递归遍历3级子目录
DIRS := $(shell find .. -maxdepth 3 -type d)
#这里循环遍历目录的cpp文件
FILES = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))

#$(warning $(FILES))

DFILES=$(FILES:.cpp=.d)

ROBJS=$(FILES:.cpp=.o)

DBGOBJS=$(FILES:.cpp=.dbg.o)

HEADS=$(BASESTRUCTFILES:.cpp=.h) ../basestruct/heads.h

Debug:$(HEADS)
Debug:$(DBGOBJS)
Debug:$(APPNAME)d

$(DBGOBJS):%.dbg.o:%.cpp
	g++ -o $@ -g -c $<

$(APPNAME)d:
	g++ -o $(APPNAME)d -g $(DBGOBJS) -lpthread

clean:
	rm -rf *.dbg.o *.o $(APPNAME) $(APPNAME)d $(DBGOBJS)
