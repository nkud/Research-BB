CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)

TARGET	 = Agent.o MovingStrategy.o ImmuneSystem.o \
		   CoupleTag.o Inheritance.o

OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Agent.o: Global.h Agent.h AgentStrategy.h Function.h Monitor.h Tag.h
$(OBJDIR)ImmuneSystem.o: AgentStrategy.h Agent.h Function.h ImmuneSystemStrategy.h

$(OBJDIR)AgentStrategy.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)MovingStrategy.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)CoupleTag.o: AgentStrategy.h Agent.h Function.h
$(OBJDIR)Inheritance.o: AgentStrategy.h Agent.h Function.h
