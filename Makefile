CC     = g++
PRINT  = /bin/echo

TARGET = main.out
SRC    = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp
OBJ    = $(SRC:.cpp=.o)
LIB    = $(SRC:.cpp=.h)

$(TARGET): $(OBJ) Global.h
	@$(PRINT) -ne 'Cretating $(TARGET)...\t'
	@$(CC) $(OBJ) -o $@
	@$(PRINT) OK!

run:
	@$(PRINT) [ run ]
	@./$(TARGET)
	@$(PRINT) [ exit ]

%.o: %.cpp %.h Global.h
	@$(PRINT) -ne 'Compiling $@...\t'
	@$(CC) -c $< -o $@
	@$(PRINT) OK!

main.o: Global.h

build: clean $(TARGET)

clean:
	@rm -rfv *.o

tags:
	@ctags $(OBJ) $(LIB) Global.h

all: tags $(TARGET) run plot

rebuild: tags build run

plot:
	@echo [ plot start ]
	@gnuplot plot2.gpi
