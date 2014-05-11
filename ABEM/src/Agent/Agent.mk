CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
INCLUDE = ../../include

VPATH = AgentStrategy $(INCLUDE)
TARGET	 = Agent.o AgentStrategy.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Global.h Agent.h AgentStrategy.h Function.h Monitor.h TagInterface.h
$(OBJDIR)AgentStrategy.o: AgentStrategy.h Agent.h Function.h
