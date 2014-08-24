#
# Virus Evolutionary Model Makefile
#
#		Author: Naoki Ueda
# Organization: OPU
#

## CONFIGURE ###################################################################
# Object Files
OBJS += main.o
OBJS += Human.o Gene.o Virus.o Cell.o Tcell.o Term.o
OBJS += ImmuneSystem.o
OBJS += Term.o FileFactory.o
OBJS += HumanCounter.o VirusCounter.o
OBJS += Function.o

output_files = log *.dat
################################################################################

## Home Directory
HOME              = ~/workspace/AgentBasedEpidemicModel/VirusEvolutionaryModel

## Command
CC                = g++ -Wall -g -O0 #-std=c++11
PRINT             = echo
MKDIR             = mkdir -vp
MAKE              = make --no-print-directory -s
COPY              = cp
RM                = rm -rfv
TAIL              = tail

## Colors
BOLDECHO          = printf '\033[1m'
REVERSEECHO       = printf '\033[7m'
REDECHO           = printf '\033[31m'
GREENECHO         = printf '\033[32m'
YELLOWECHO        = printf '\033[33m'
BLUEECHO          = printf '\033[34m'
CLRECHO           = printf '\033[0m\033[39m'
COLORECHO         = $(BOLDECHO); $(BLUEECHO)

## Directory Names
SRC		 = $(shell find src -name '*.cpp')
INCLUDE  = $(shell find include -name '*.h' -or -name '*.hpp')

object_dir	 = obj
SRCDIR	 = src
INCDIR   = include
SCRDIR	 = script
BINDIR	 = bin
PRGDIR	 = program
MSTDIR	 = master
clean_directory = $(BINDIR) $(object_dir)
bin_clean_files = $(output_files)

now			= $(shell date +%y%m%d-%H%M%S)
timestamp	:= $(shell date '+< %y/%m/%d %H:%M:%S >')
TIME		:= $(shell date +%y%m%d-%H%M%S)
RSTDIR		= result-$(now)
PRGNAME		= program-$(now)

CPPFLAGS = $(addprefix -I , $(INCDIR))

vpath %.cpp src
vpath %.hpp include
vpath %.o	obj

## Target
EXE := VEM.exe
TARGET := $(BINDIR)/$(EXE)
#OUTOBJ   = $(addprefix $(object_dir)/, $(addsuffix .o, $(notdir $(basename $(INCLUDE)))))
OUTOBJ = $(addprefix $(object_dir)/, $(OBJS))

.PHONY: target all run gene clean


target: $(TARGET)

all: $(TARGET) run tail

# Dependency ###################################################################
$(object_dir)/main.o: Human.hpp Virus.hpp Config.hpp ImmuneSystem.hpp Function.hpp Tcell.hpp

$(object_dir)/Human.o: Human.hpp Gene.hpp Virus.hpp ImmuneSystem.hpp Cell.hpp Mobile.hpp Landscape.hpp Host.hpp
$(object_dir)/Config.o: Config.hpp
$(object_dir)/Gene.o: Gene.hpp
$(object_dir)/Cell.o: Cell.hpp Function.hpp Virus.hpp Host.hpp
$(object_dir)/Virus.o: Virus.hpp Gene.hpp
$(object_dir)/Tcell.o: Tcell.hpp Gene.hpp Mobile.hpp
$(object_dir)/ImmuneSystem.o: ImmuneSystem.hpp Virus.hpp Cell.hpp Function.hpp

$(object_dir)/HumanCounter.o: HumanCounter.hpp
$(object_dir)/VirusCounter.o: VirusCounter.hpp

$(object_dir)/Term.o: Term.hpp
$(object_dir)/FileFactory.o: FileFactory.hpp Term.hpp Function.hpp
$(object_dir)/Function.o: Function.hpp Random.hpp
################################################################################

## Make Program
$(TARGET): $(OUTOBJ)
	@$(COLORECHO)
	@$(PRINT) -n '==> Linking $(notdir $@)...'
	@$(CLRECHO)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	@$(CC) $^ -o $@ $(CPPFLAGS)
	@$(PRINT) 'ok'

$(object_dir)/%.o: %.cpp
	@$(COLORECHO)
	@$(PRINT) -n '==> Compiling $(notdir $@)...'
	@$(CLRECHO)
	@[ -d $(object_dir) ] || $(MKDIR) $(object_dir)
	@$(CC) -c $< -o $@ $(CPPFLAGS)
	@$(PRINT) 'ok'

## Other Actions
run: bclean
	@$(COLORECHO)
	@$(PRINT) '==> Program is started $(timestamp)'
	@$(CLRECHO)
	@echo run > log
	@cd $(BINDIR); ./$(EXE)
	@$(COLORECHO)
	@$(PRINT) '==> Terminated $(timestamp)'
	@$(CLRECHO)

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
	tree $(INCDIR) $(SRCDIR) $(object_dir) $(BINDIR) $(SCRDIR)

time:
	@$(COLORECHO)
	@$(PRINT) '==> $(now)'
	@$(CLRECHO)

bclean:
	@$(COLORECHO)
	@$(PRINT) '==> Cleanning bin/ $(bin_clean_files)'
	@$(CLRECHO)
	@cd $(BINDIR); $(RM) $(bin_clean_files)

tail:
	@$(COLORECHO)
	@$(PRINT) '==> Log tail'
	@$(CLRECHO)
	@cd $(BINDIR); $(TAIL) log

re: clean $(TARGET)
