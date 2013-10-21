TARGET = main.out
SRC = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp
OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ) Global.h
	@echo -n "Cretating $(TARGET)...\t" 
	@g++ $(OBJ) -o $@
	@echo "OK!"

run:
	@echo "[ run ]"
	@./$(TARGET)
	@echo "[ exit ]"

%.o: %.cpp %.h Global.h
	@echo -n "Compiling $@...\t" 
	@g++ -c $< -o $@
	@echo "OK!"

build: clean $(TARGET)

clean:
	@rm -rfv *.o

all: $(TARGET) run
