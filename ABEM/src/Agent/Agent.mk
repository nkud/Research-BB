CC       = g++ -Wall -g -O0
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)
	
TARGET	 = Agent.o MovingStrategy.o ImmuneSystem.o \
		   CoupleTag.o Inheritance.o AgentCounter.o \
		   AgentManager.o

OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Global.h Agent.h AgentStrategy.h Function.h Gene.h
$(OBJDIR)ImmuneSystem.o: Global.h AgentStrategy.h Agent.h Function.h ImmuneSystemStrategy.h

$(OBJDIR)AgentStrategy.o: Global.h AgentStrategy.h Agent.h Function.h
$(OBJDIR)MovingStrategy.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)CoupleTag.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)Inheritance.o: AgentStrategy.h Agent.h Function.h

$(OBJDIR)AgentCounter.o: AgentCounter.h
$(OBJDIR)AgentManager.o: AgentManager.h Global.h Agent.h Virus.h
