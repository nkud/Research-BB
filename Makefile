CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
CTAGS    = $(shell which ctags)

OBJ      = $(SRC:.cpp=.o)
LIB      = $(SRC:.cpp=.h)

TARGET   = main.out
SRC      = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp

VPATH    = src include
CPPFLAGS = -I include

$(TARGET): $(OBJ) Global.h
	@$(PRINT) -ne 'Cretating $(TARGET)...\t'
	@$(CC) $(OBJ) -o $@
	@$(PRINT) OK!

.PHONY: run clean build rebuild

run:
	@$(PRINT) [ run ]
	@./$(TARGET)
	@$(PRINT) [ exit ]

%.o: %.cpp
	@$(PRINT) -ne 'Compiling $@...\t'
	@$(CC) -c $< -o $@ $(CPPFLAGS)
	@$(PRINT) OK!

main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h
Administrator.o: Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
Monitor.o: Monitor.h Global.h
TagInterface.o: TagInterface.h Global.h
Agent.o: Agent.h Function.h Monitor.h
Virus.o: Virus.h Function.h
Landscape.o: Landscape.h
Function.o: Function.h

build: clean $(TARGET)

clean:
	@$(RM) *.o

tags:
	@$(CTAGS) $(wildcard src/*) $(wildcard include/*)

all: $(TARGET) run plot

rebuild: tags build run plot

plot :
	@echo [ plot start ]
	@gnuplot plot2.gpi
