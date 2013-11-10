CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
CTAGS    = ctags

OBJ      = $(SRC:.cpp=.o)
LIB      = $(SRC:.cpp=.h)

TARGET   = main.out
SRC      = main.cpp Virus.cpp Agent.cpp Function.cpp TagInterface.cpp Monitor.cpp Administrator.cpp Landscape.cpp

VPATH    = src include
CPPFLAGS = -I include

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
	@$(CC) -c $< -o $@ $(CPPFLAGS)
	@$(PRINT) OK!

main.o: Global.h

build: clean $(TARGET)

clean:
	@$(RM) -rfv *.o

tags:
	@$(CTAGS) $(SRC) $(LIB) Global.h

all: $(TARGET) run plot

rebuild: tags build run

plot:
	@echo [ plot start ]
	@gnuplot plot2.gpi
