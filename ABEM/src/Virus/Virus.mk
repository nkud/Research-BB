CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj/
LIBDIR = ../../include

INCLUDE := $(shell find $(LIBDIR) -type d)
CPPFLAGS     = $(addprefix -I, $(INCLUDE))

SRCDIR := $(shell find . -type d)

VPATH = $(INCLUDE) $(SRCDIR) $(OBJDIR)

TARGET	 = Virus.o NormalVirus.o FixedVirus.o VirusStrategy.o


OBJS = $(addprefix $(OBJDIR), $(TARGET))


all: $(OBJS)

$(OBJDIR)%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)Virus.o: Global.h Virus.h Function.h
$(OBJDIR)NormalVirus.o: NormalVirus.h VirusStrategy.h
$(OBJDIR)FixedVirus.o: FixedVirus.h VirusStrategy.h
