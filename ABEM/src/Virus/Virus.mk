CC       = g++ -Wall -Wall -g -O0
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)

TARGET	 = Virus.o NormalVirus.o FixedVirus.o VirusStrategy.o \
		   VirusCounter.o VirusManager.o


OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Virus.o: Global.h Virus.h Function.h SearchStrategy.h
$(OBJDIR)NormalVirus.o: NormalVirus.h VirusStrategy.h SearchStrategy.h
$(OBJDIR)FixedVirus.o: FixedVirus.h VirusStrategy.h SearchStrategy.h
$(OBJDIR)VirusCounter.o: Global.h
$(OBJDIR)VirusManager.o: Global.h
