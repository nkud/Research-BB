#
# Virus Evolutionary Model Makefile
#
#		Author: Naoki Ueda
# Organization: OPU
#

## Home Directory
HOME              = ~/workspace/AgentBasedEpidemicModel/VirusEvolutionaryModel

## Command
CC                = /usr/bin/g++ -Wall -g -O0 -std=c++11
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

OBJDIR	 = ./obj
SRCDIR	 = ./src
INCDIR   = ./include
BINDIR	 = ./bin
PRGDIR	 = ./program
MSTDIR	 = ./master

NOW		 := $(shell date +%y%m%d-%H%M%S)
RSTDIR   = result-$(NOW)
PRGNAME  = program-$(NOW)

CPPFLAGS = $(addprefix -I, $(INCDIR))

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
# Objects
OBJS = Human.o Gene.o Virus.o Cell.o Tcell.o Term.o
OBJS += Term.o FileFactory.o Random.o
OBJS += HumanCounter.o VirusCounter.o

# dependency
$(OBJDIR)/Human.o: Human.hpp Gene.hpp
$(OBJDIR)/Config.o: Config.hpp
$(OBJDIR)/Gene.o: Gene.hpp
$(OBJDIR)/Cell.o: Cell.hpp Function.hpp
$(OBJDIR)/Virus.o: Virus.hpp Gene.hpp
$(OBJDIR)/Tcell.o: Gene.hpp

$(OBJDIR)/HumanCounter.o: HumanCounter.hpp
$(OBJDIR)/VirusCounter.o: VirusCounter.hpp

$(OBJDIR)/Term.o: Term.hpp
$(OBJDIR)/FileFactory.o: FileFactory.hpp
################################################################################

## Make Program
$(TARGET): main.cpp $(OUTOBJ)
	@$(COLORECHO)
	@$(PRINT) '==> Creating $@...'
	@$(CLRECHO)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	$(CC) $^ -o $@ $(CPPFLAGS)

$(OBJDIR)/%.o: %.cpp
	@$(COLORECHO)
	@$(PRINT) '==> Creating $@...'
	@$(CLRECHO)
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	$(CC) -c $< -o $@ $(CPPFLAGS)

## Other Actions
run: $(TARGET)
	@./$<

clean:
	@$(COLORECHO)
	@$(PRINT) '==> Cleanning...'
	@$(CLRECHO)
	@$(RM) $(BINDIR) $(OBJDIR)

zip:
	@$(COLORECHO)
	@$(PRINT) '==> Zipping...'
	@$(CLRECHO)

tree:
	tree $(INCDIR) $(SRCDIR) $(OBJDIR) $(BINDIR)

build: clean $(TARGET)
