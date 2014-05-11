CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
INCLUDE = ../../include/

VPATH = $(INCLUDE)
TARGET	 = main.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)main.o: Global.h Function.h Agent.h Virus.h Landscape.h Monitor.h Administrator.h FileFactory.h
