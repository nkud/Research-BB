main.out: main.o Virus.o Agent.o

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -rfv *.o
