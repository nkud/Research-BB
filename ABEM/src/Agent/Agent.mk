CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
INCLUDE = ../../include

vpath %.h $(INCLUDE)
vpath %.cpp ImmuneSystem
vpath %.cpp AgentStrategy
vpath %.cpp AgentStrategy/MovingStrategy
vpath %.cpp AgentStrategy/ChildBirthStrategy
vpath %.cpp AgentStrategy/AgingStrategy

TARGET	 = Agent.o AgentStrategy.o MovingStrategy.o ChildBirthStrategy.o ImmuneSystem.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Global.h Agent.h AgentStrategy.h Function.h Monitor.h TagInterface.h
$(OBJDIR)AgentStrategy.o: AgentStrategy.h Agent.h Function.h
