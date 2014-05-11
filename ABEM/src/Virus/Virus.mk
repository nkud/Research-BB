CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
INCLUDE = ../../include

VPATH = VirusStrategy $(INCLUDE)
TARGET	 = Virus.o VirusStrategy.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR), $(TARGET))

all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Virus.o: Global.h Virus.h Function.h
$(OBJDIR)VirusStrategy.o: VirusStrategy.h
