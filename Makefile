CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
MKDIR	 = mkdir -vp
COPY	 = cp

BIN		 = bin
MASTER	 = master

CTAGS    = $(shell which ctags)

NOW		 = $(shell date +"%m%d%I%M%S")

OBJ      = $(addprefix bin/, $(SRC:.cpp=.o))
LIB      = $(SRC:.cpp=.h)

TARGET   = main.out
SRC      = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp FileFactory.cpp

VPATH    = src include
CPPFLAGS = -I include

$(BIN)/$(TARGET): $(OBJ)
	@$(PRINT) -n 'Cretating $<...'
	@$(CC) $(OBJ) -o $@
	@$(PRINT) OK!

.PHONY: run clean build rebuild

run:
	@$(PRINT) [ run ]
	@cd $(BIN); ./$(TARGET)
	@$(PRINT) [ exit ]

$(BIN)/%.o: %.cpp
	@$(PRINT) -n ">>> Compiling $@..."
	@$(CC) -c $< -o $@ $(CPPFLAGS)
	@$(PRINT) OK!

build: clean tags $(BIN)/$(TARGET)

clean:
	@$(PRINT) '>>> Cleaning...'
	@$(RM) $(OBJ)

tags:
	@$(CTAGS) $(wildcard src/*) $(wildcard include/*)

all: $(BIN)/$(TARGET) run plot

plot :
	@$(PRINT) '>>> Plotting...'
	@-cd $(BIN); python peak_search.py
	@-cd $(BIN); gnuplot auto.plt
	@cd $(BIN); mkdir -p txt;  mv *.txt txt
	@cd $(BIN); mkdir -p img;  mv *.png img
	@cd $(BIN); mkdir -p script;  mv *.plt script

pack:
	@$(PRINT) '>>> Packing...'
	@$(MKDIR) $(MASTER)
	@cd $(MASTER); $(MKDIR) $(NOW)
	@cd $(MASTER); $(MKDIR) $(NOW)/txt
	@cd $(MASTER); $(MKDIR) $(NOW)/src
	@cd $(MASTER); $(MKDIR) $(NOW)/img
	@cd $(MASTER); $(MKDIR) $(NOW)/script
	@$(COPY) $(BIN)/txt/*.txt $(MASTER)/$(NOW)/txt
	@$(COPY) $(BIN)/script/*.plt $(MASTER)/$(NOW)/script
	@$(COPY) $(BIN)/img/*.png $(MASTER)/$(NOW)/img
	@$(COPY) include/Global.h src/main.cpp $(MASTER)/$(NOW)/src
	@cd $(BIN); $(COPY) note.html RESULT.html result.css ../$(MASTER)/$(NOW)
	@tree $(MASTER)/$(NOW)

$(BIN)/main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h FileFactory.h
$(BIN)/Administrator.o: Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
$(BIN)/Monitor.o: Monitor.h Global.h
$(BIN)/TagInterface.o: TagInterface.h Global.h
$(BIN)/Agent.o: Agent.h Function.h Monitor.h Global.h TagInterface.h
$(BIN)/Virus.o: Global.h Virus.h Function.h TagInterface.h
$(BIN)/Landscape.o: Landscape.h
$(BIN)/Function.o: Function.h
$(BIN)/FileFactory.o: Administrator.h Agent.h Virus.h Global.h

Administrator.h: Global.h
Agent.h: Global.h TagInterface.h Virus.h
Virus.h: TagInterface.h
Landscape.h: Global.h
TagInterface.h: Global.h
Function.h: Global.h
