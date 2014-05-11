CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/

VPATH = AgentStrategy
TARGET	 = Agent.o AgentStrategy.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS)
