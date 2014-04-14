TARGET	= ABEM.out

CC       = g++

SUBDIRS := TagInterface Agent AgentStrategy Virus AdministratorStrategy \
		   Landscape Monitor FileFactory Benchmark Function \
		   Administrator

DIRS = Tag Agent Virus Administrator Landscape Monitor FileFactory Benchmark Function

VPATH = $(DIRS)

OBJDIR	= obj
OBJS	:= $(addprefix $(OBJDIR)/, $(SUBDIRS:=.o))

INCLUDE	= -I include

$(TARGET): $(OBJS) obj/main.o
	@echo make
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(INCLUDE)


all: clean $(TARGET)

clean:
	@echo -n Cleaning...
	@rm -rvf $(OBJDIR) $(TARGET)
