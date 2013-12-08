CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
MKDIR	 = mkdir -vp
COPY	 = cp

BIN		 = bin

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

pack:
	@$(PRINT) '>>> Packing...'
	@$(MKDIR) $(NOW)
	@$(MKDIR) $(NOW)/txt
	@$(MKDIR) $(NOW)/src
	@$(MKDIR) $(NOW)/img
	@$(MKDIR) $(NOW)/script
	@$(COPY) $(BIN)/txt/*.txt $(NOW)/txt
	@$(COPY) $(BIN)/script/*.plt $(NOW)/script
	@$(COPY) $(BIN)/img/*.png $(NOW)/img
	@$(COPY) include/Global.h src/main.cpp $(NOW)/src
	@cd $(BIN); $(COPY) RESULT.html result.css main.out ../$(NOW)
	@tree $(NOW)

plot :
	@$(PRINT) [ start plot ]
	@cd $(BIN); gnuplot auto.plt
	@cd $(BIN); mkdir -p txt;  mv *.txt txt
	@cd $(BIN); mkdir -p img;  mv *.png img
	@cd $(BIN); mkdir -p script;  mv *.plt script
	@$(PRINT) [ end plot ]

$(BIN)/main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h
$(BIN)/Administrator.o: Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
$(BIN)/Monitor.o: Monitor.h Global.h
$(BIN)/TagInterface.o: TagInterface.h Global.h
$(BIN)/Agent.o: Agent.h Function.h Monitor.h Global.h TagInterface.h
$(BIN)/Virus.o: Global.h Virus.h Function.h TagInterface.h
$(BIN)/Landscape.o: Landscape.h
$(BIN)/Function.o: Function.h
$(BIN)/FileFactory.o: Administrator.h Agent.h Virus.h Global.h
