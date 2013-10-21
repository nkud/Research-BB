CC     = g++
PRINT  = /bin/echo

TARGET = main.out
SRC    = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp
OBJ    = $(SRC:.cpp=.o)
LIB    = $(SRC:.cpp=.h)

$(TARGET): $(OBJ) Global.h
	@$(PRINT) -n "Cretating $(TARGET)...\t" 
	@$(CC) $(OBJ) -o $@
	@$(PRINT) "OK!"

run:
	@$(PRINT) "[ run ]"
	@./$(TARGET)
	@$(PRINT) "[ exit ]"

%.o: %.cpp %.h Global.h
	@$(PRINT) -n "Compiling $@...\t" 
	@$(CC) -c $< -o $@
	@$(PRINT) "OK!"

main.o: Global.h

build: clean $(TARGET)

clean:
	@rm -rfv *.o

tags:
	@ctags $(OBJ) $(LIB) Global.h

all: tags $(TARGET) run

rebuild: tags build run
