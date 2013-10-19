main.out: Virus.o

%.o: %.cpp
	g++ -c $< -o $@
