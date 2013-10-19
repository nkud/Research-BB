main.out: Virus.o Agent.o

%.o: %.cpp
	g++ -c $< -o $@
