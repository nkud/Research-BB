CC       = g++ -Wall -g -O0
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR)

TARGET	 = Administrator.o AdministratorStrategy.o NonOverlappingStrategy.o

OBJS = $(addprefix $(OBJDIR)/, $(TARGET))


all: $(OBJS)

$(OBJDIR)/%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)/Administrator.o:  Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
$(OBJDIR)/AdministratorStrategy.o: Global.h Administrator.h Landscape.h Agent.h AdministratorStrategy.h Monitor.h Function.h
$(OBJDIR)/NonOverlappingStrategy.o: Global.h NonOverlappingStrategy.h Administrator.h Landscape.h Agent.h Monitor.h Function.h
