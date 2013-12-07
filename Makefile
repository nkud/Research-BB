CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
MKDIR	 = mkdir -v
COPY	 = cp

CTAGS    = $(shell which ctags)

NOW		 = $(shell date +"%m%d%I%M%S")

OBJ      = $(SRC:.cpp=.o)
LIB      = $(SRC:.cpp=.h)

TARGET   = main.out
SRC      = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp

VPATH    = src include
CPPFLAGS = -I include

$(TARGET): $(OBJ)
	@$(PRINT) -n 'Cretating $(TARGET)...'
	@$(CC) $(OBJ) -o $@
	@$(PRINT) OK!

.PHONY: run clean build rebuild

run:
	@$(PRINT) [ run ]
	@./$(TARGET)
	@$(PRINT) [ exit ]

%.o: %.cpp
	@$(PRINT) -n ">>> Compiling $@..."
	@$(CC) -c $< -o $@ $(CPPFLAGS)
	@$(PRINT) OK!

main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h
Administrator.o: Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
Monitor.o: Monitor.h Global.h
TagInterface.o: TagInterface.h Global.h
Agent.o: Agent.h Function.h Monitor.h Global.h TagInterface.h
Virus.o: Virus.h Function.h TagInterface.h
Landscape.o: Landscape.h
Function.o: Function.h

build: clean tags $(TARGET)

clean:
	@$(PRINT) '>>> Cleaning...'
	@$(RM) *.o

tags:
	@$(CTAGS) $(wildcard src/*) $(wildcard include/*)

all: $(TARGET) run plot

pack:
	@$(PRINT) '>>> Packing...'
	@$(MKDIR) $(NOW)
	@$(MKDIR) $(NOW)/txt
	@$(MKDIR) $(NOW)/src
	@$(COPY) *.txt $(NOW)/txt
	@$(COPY) include/Global.h src/main.cpp $(NOW)/src
	@$(COPY) *.png *.plt RESULT.html result.css main.out $(NOW)
	@tree $(NOW)

plot :
	@$(PRINT) [ start plot ]
	@gnuplot auto.plt
	@gnuplot quick.plt
	@$(PRINT) [ end plot ]
