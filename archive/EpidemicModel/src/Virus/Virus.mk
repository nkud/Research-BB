CC       = g++ -Wall -Wall -g -O0
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)

TARGET	 = Virus.o VirusCounter.o VirusManager.o NormalVirus.o


OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Virus.o: Config.h VirusInterface.hpp Function.h Gene.h VirusCounter.h

$(OBJDIR)VirusCounter.o: Config.h VirusCounter.h VirusInterface.hpp Function.h
$(OBJDIR)VirusManager.o: Config.h VirusInterface.hpp VirusManager.h

$(OBJDIR)NormalVirus.o: Config.h NormalVirus.hpp Function.h

NormalVirus.hpp: VirusInterface.hpp
