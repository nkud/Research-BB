main.out: main.o Virus.o Agent.o Function.o

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -rfv *.o
