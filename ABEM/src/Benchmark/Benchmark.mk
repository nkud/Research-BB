CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/

VPATH = 
TARGET	 = Benchmark.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@$(CC) -c $< -o $@ $(CPPFLAGS)
