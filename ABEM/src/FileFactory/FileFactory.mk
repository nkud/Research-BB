CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)

TARGET	 = FileFactory.o


OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)FileFactory.o: FileFactory.h Administrator.h Agent.h Virus.h Global.h Monitor.h Benchmark.h
