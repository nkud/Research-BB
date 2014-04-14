OUT		= ABEM.out
TARGET	= $(BIN)/$(OUT)

CC       = g++
PRINT    = /bin/echo
RM       = rm -rfv
MKDIR	 = mkdir -vp
COPY	 = cp
CTAGS    = $(shell which ctags)
NOW		 = $(shell date +"%y%m%d%H%M%S")

DIR = Tag Agent Virus Administrator Landscape \
	  Monitor FileFactory Benchmark Function

DIRS = $(addprefix src/, $(DIR))

OBJDIR	= obj
BIN = bin

SRCS = $(shell find $(DIRS) -name '*.cpp')

VPATH = $(DIRS)

OBJS	:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

INCLUDE	= -I include


$(TARGET): $(OBJS) $(OBJDIR)/main.o
	@[ -d $(BIN) ] || mkdir -p $(BIN)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(INCLUDE)

clean:
	@$(PRINT) [ clean ]
	@$(RM) -rvf $(OBJDIR) $(BIN)

run:
	@$(PRINT) [ run ]
	@cd $(BIN); ./$(OUT)

tags:
	@$(CTAGS) $(SRCS)

gene:
	@$(PRINT) '>>> Generate...'
	@cd $(BIN); python ../script/gene.py
	@-cd $(BIN); gnuplot auto.plt

all: clean $(TARGET) run gene
build: clean $(TARGET)
