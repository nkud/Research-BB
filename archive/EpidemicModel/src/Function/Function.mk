CC       = g++ -Wall -g -O0 -std=c++11
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)
	
TARGET	 = Function.o Random.o

OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

test:

clean:

$(OBJDIR)Random.o: Random.hpp
$(OBJDIR)Function.o: Terminal.hpp
