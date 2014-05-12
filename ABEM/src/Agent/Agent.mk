CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

vpath %.h $(INCLUDE)
vpath %.cpp ImmuneSystem
vpath %.cpp AgentStrategy
vpath %.cpp AgentStrategy/MovingStrategy
vpath %.cpp AgentStrategy/ChildBirthStrategy
vpath %.cpp AgentStrategy/AgingStrategy

TARGET	 = Agent.o MovingStrategy.o ImmuneSystem.o \
		   CoupleTag.o Inheritance.o

OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Global.h Agent.h AgentStrategy.h Function.h Monitor.h Tag.h
$(OBJDIR)AgentStrategy.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)ImmuneSystem.o: AgentStrategy.h Agent.h Function.h ImmuneSystemStrategy.h
