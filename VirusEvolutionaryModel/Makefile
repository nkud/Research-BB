#
# Virus Evolutionary Model Makefile
#
# 		Author: Naoki Ueda
# Organization: OPU
#

## Home Directory
HOME	 = ~/workspace/AgentBasedEpidemicModel/VirusEvolutionaryModel

## Command
CC       = /usr/bin/g++ -Wall -g -O0
PRINT    = /bin/echo
MKDIR	 = mkdir -vp
MAKE	 = make --no-print-directory -s
COPY	 = cp
RM		 = rm -rfv

## Colors
BOLDECHO  = printf '\033[1m'
REVERSEECHO  = printf '\033[7m'
REDECHO  = printf '\033[31m'
GREENECHO  = printf '\033[32m'
BLUEECHO  = printf '\033[34m'
CLRECHO	 = printf '\033[0m\033[39m'
COLORECHO = $(BOLDECHO); $(BLUEECHO)

## Directory Names
SRC		 = $(shell find src -name '*.cpp')
INCLUDE  = $(shell find include -name '*.h' -or -name '*.hpp')

OBJDIR	 = obj
SRCDIR	 = src
INCDIR   = include
BINDIR	 = bin
PRGDIR	 = program
MSTDIR	 = master

NOW		 := $(shell date +%y%m%d-%H%M%S)
RSTDIR   = result-$(NOW)
PRGNAME  = program-$(NOW)

CPPFLAGS = $(addprefix -I, $(INCDIR))

vpath %.cpp src
vpath %.hpp include
vpath %.o 	obj

## Target
OUTPUT := VEM.exe
TARGET := $(BINDIR)/$(OUTPUT)
OBJS   = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(INCLUDE)))))


.PHONY: all run gene clean

$(TARGET): main.cpp $(OBJS)
	@$(COLORECHO)
	@$(PRINT) '==> Creating $@...'
	@$(CLRECHO)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	$(CC) $< -o $@ $(CPPFLAGS)


$(OBJDIR)/%.o: %.cpp
	@$(COLORECHO)
	@$(PRINT) '==> Creating $@...'
	@$(CLRECHO)
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	$(CC) -c $< -o $@ $(CPPFLAGS)

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

all: clean $(TARGET)

