#
# Virus Evolutionary Model Makefile
#
#		Author: Naoki Ueda
# Organization: OPU
#

## Home Directory
HOME              = ~/workspace/AgentBasedEpidemicModel/VirusEvolutionaryModel

## Command
CC                = /usr/bin/g++ -Wall -g -O0 # -std=c++11
PRINT             = /bin/echo
MKDIR             = mkdir -vp
MAKE              = make --no-print-directory -s
COPY              = cp
RM                = rm -rfv

## Colors
BOLDECHO          = printf '\033[1m'
REVERSEECHO       = printf '\033[7m'
REDECHO           = printf '\033[31m'
GREENECHO         = printf '\033[32m'
BLUEECHO          = printf '\033[34m'
CLRECHO           = printf '\033[0m\033[39m'
COLORECHO         = $(BOLDECHO); $(BLUEECHO)

## Directory Names
SRC		 = $(shell find src -name '*.cpp')
INCLUDE  = $(shell find include -name '*.h' -or -name '*.hpp')

OBJDIR	 = obj
SRCDIR	 = src
INCDIR   = include
SCRDIR	 = script
BINDIR	 = bin
PRGDIR	 = program
MSTDIR	 = master
clean_directory = $(BINDIR) $(OBJDIR)

NOW		 := $(shell date +%y%m%d-%H%M%S)
RSTDIR   = result-$(NOW)
PRGNAME  = program-$(NOW)

CPPFLAGS = $(addprefix -I , $(INCDIR))

vpath %.cpp src
vpath %.hpp include
vpath %.o	obj

## Target
EXE := VEM.exe
TARGET := $(BINDIR)/$(EXE)
#OUTOBJ   = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(INCLUDE)))))
OUTOBJ = $(addprefix $(OBJDIR)/, $(OBJS))

.PHONY: all run gene clean


all: $(TARGET)

## CONFIGURE ###################################################################
# Object Files
OBJS += main.o
OBJS += Human.o Gene.o Virus.o Cell.o Tcell.o Term.o
OBJS += ImmuneSystem.o
OBJS += Term.o FileFactory.o
OBJS += HumanCounter.o VirusCounter.o
OBJS += Function.o

# Dependency
$(OBJDIR)/main.o: Human.hpp Virus.hpp Config.hpp ImmuneSystem.hpp Function.hpp Tcell.hpp

$(OBJDIR)/Human.o: Human.hpp Gene.hpp Virus.hpp ImmuneSystem.hpp Cell.hpp Mobile.hpp Landscape.hpp
$(OBJDIR)/Config.o: Config.hpp
$(OBJDIR)/Gene.o: Gene.hpp
$(OBJDIR)/Cell.o: Cell.hpp Function.hpp Virus.hpp
$(OBJDIR)/Virus.o: Virus.hpp Gene.hpp
$(OBJDIR)/Tcell.o: Tcell.hpp Gene.hpp Mobile.hpp
$(OBJDIR)/ImmuneSystem.o: ImmuneSystem.hpp Virus.hpp Cell.hpp

$(OBJDIR)/HumanCounter.o: HumanCounter.hpp
$(OBJDIR)/VirusCounter.o: VirusCounter.hpp

$(OBJDIR)/Term.o: Term.hpp
$(OBJDIR)/FileFactory.o: FileFactory.hpp
$(OBJDIR)/Function.o: Function.hpp Random.hpp
################################################################################

## Make Program
$(TARGET): $(OUTOBJ)
	@$(COLORECHO)
	@$(PRINT) '==> Linking $(notdir $@)'
	@$(CLRECHO)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	@$(CC) $^ -o $@ $(CPPFLAGS)

$(OBJDIR)/%.o: %.cpp
	@$(COLORECHO)
	@$(PRINT) '==> Compiling $(notdir $@)'
	@$(CLRECHO)
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

## Other Actions
run: $(TARGET)
	@./$<

clean:
	@$(COLORECHO)
	@$(PRINT) '==> Cleanning $(clean_directory)'
	@$(CLRECHO)
	@$(RM) $(clean_directory)

zip:
	@$(COLORECHO)
	@$(PRINT) '==> Zipping...'
	@$(CLRECHO)

tree:
	tree $(INCDIR) $(SRCDIR) $(OBJDIR) $(BINDIR) $(SCRDIR)

time:
	@$(COLORECHO)
	@$(PRINT) '==> $(NOW)'
	@$(CLRECHO)


build: clean $(TARGET)
