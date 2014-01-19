CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
MKDIR	 = mkdir -vp
COPY	 = cp

BIN		 = bin
MASTER	 = master

CTAGS    = $(shell which ctags)

NOW		 = $(shell date +"%y%m%d%H%M%S")

OBJ      = $(addprefix bin/, $(SRC:.cpp=.o))
LIB      = $(SRC:.cpp=.h)

TARGET   = main.out
SRC      = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp FileFactory.cpp Benchmark.cpp AgentStrategy.cpp

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
	@$(RM) $(BIN)/assets
	@$(RM) $(BIN)/*.txt
	@$(RM) $(BIN)/*.out
	@$(RM) $(BIN)/*.html

tags:
	@$(CTAGS) $(wildcard src/*) $(wildcard include/*)

all: $(BIN)/$(TARGET) run gene

gene :
	@$(PRINT) '>>> Generate...'
	@cd $(BIN); python ../script/gene.py
	@-cd $(BIN); gnuplot auto.plt

pack:
	@$(PRINT) '>>> Packing...'
	@$(MKDIR) $(MASTER)
	@cd $(MASTER); $(MKDIR) $(NOW)
	@cd $(MASTER); $(MKDIR) $(NOW)/src
	@cd $(MASTER); $(MKDIR) $(NOW)/assets
	@cd $(MASTER); $(MKDIR) $(NOW)/script
	@$(COPY) $(BIN)/*.txt $(MASTER)/$(NOW)/assets
	@$(COPY) $(BIN)/*.plt $(MASTER)/$(NOW)/script
	@$(COPY) $(BIN)/*.png $(MASTER)/$(NOW)
	@$(COPY) include/Global.h src/main.cpp $(MASTER)/$(NOW)/src
	@cd $(BIN); $(COPY) index.html result.css ../$(MASTER)/$(NOW)
	@tree $(MASTER)/$(NOW)

$(BIN)/main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h FileFactory.h
$(BIN)/Administrator.o: Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
$(BIN)/Monitor.o: Monitor.h Global.h
$(BIN)/TagInterface.o: TagInterface.h Global.h
$(BIN)/Agent.o: AgentStrategy.h Agent.h Function.h Monitor.h Global.h TagInterface.h
$(BIN)/AgentStrategy.o: AgentStrategy.h Agent.h
$(BIN)/Virus.o: Global.h Virus.h Function.h TagInterface.h
$(BIN)/Landscape.o: Global.h Landscape.h Function.h
$(BIN)/Function.o: Function.h
$(BIN)/FileFactory.o: Administrator.h Agent.h Virus.h Global.h
$(BIN)/Benchmark.o: Benchmark.h

Administrator.h: Global.h
Agent.h: TagInterface.h Virus.h AgentStrategy.h
AgentStrategy.h: Agent.h
Virus.h: TagInterface.h
Landscape.h: Global.h
TagInterface.h: Global.h
Function.h: Global.h
Benchmark: 
