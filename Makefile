TARGET = main.out
OBJ = main.o Virus.o Agent.o Function.o TagInterface.o

$(TARGET): $(OBJ)
	@echo -n "Cretating $(TARGET)...\t" 
	@g++ $(OBJ) -o $@
	@echo "OK!"

run:
	@echo "[ run ]"
	@./$(TARGET)
	@echo "[ exit ]"

%.o: %.cpp %.h
	@echo -n "Compiling $@...\t" 
	@g++ -c $< -o $@
	@echo "OK!"

clean:
	@rm -rfv *.o

all: $(TARGET) run
