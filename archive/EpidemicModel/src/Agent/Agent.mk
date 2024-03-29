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
		   		 AgentCounter.o AgentManager.o

OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Agent.h AgentStrategy.h Function.h Gene.h
$(OBJDIR)ImmuneSystem.o: AgentStrategy.h Agent.h Function.h \
						 ImmuneSystem.h AgentCounter.h VirusCounter.h

$(OBJDIR)MovingStrategy.o: AgentStrategy.h Agent.h Function.h

$(OBJDIR)AgentCounter.o: AgentCounter.h
$(OBJDIR)AgentManager.o: AgentManager.h Agent.h VirusInterface.hpp Landscape.h Function.h
