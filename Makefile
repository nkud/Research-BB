OBJ = main.o Virus.o Agent.o Function.o TagInterface.o

main.out: $(OBJ)
	g++ $(OBJ) -o $@

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -rfv *.o
