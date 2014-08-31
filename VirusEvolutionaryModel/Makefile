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
OBJS += Term.o FileFactory.o
OBJS += HumanCounter.o VirusCounter.o
OBJS += Function.o
OBJS += Host.o

output_files = log *.txt
################################################################################

## Home Directory
HOME = ~/workspace/AgentBasedEpidemicModel/VirusEvolutionaryModel

## Command
CC    = g++ -Wall -g -O0 -std=c++11
PRINT = echo
MKDIR = mkdir -p
MAKE  = make --no-print-directory -s
COPY  = cp
RM    = rm -rfv
TAIL  = tail
PLOT  = gnuplot
PY    = python
DISPLAY = feh

include colors.mk

## Directory Names
SRC            = $(shell find src -name '*.cpp')
INCLUDE        = $(shell find include -name '*.h' -or -name '*.hpp')

object_dir     = obj
SRCDIR         = src
INCDIR         = include
include_subdir = $(shell find $(INCDIR) -type d)
src_subdir = $(shell find $(SRCDIR) -type d)
SCRDIR         = script
BINDIR         = bin
PRGDIR         = program
MSTDIR         = master
test_dir       = test
stat_dir       = stat
test_make_name = test.mk

clean_directory = $(BINDIR) $(object_dir) $(stat_dir)
bin_clean_files = $(output_files)
test_make_file	= $(test_dir)/$(test_make_name)

now			= $(shell date +%y%m%d-%H%M%S)
timestamp	:= $(shell date '+< %y/%m/%d %H:%M:%S >')
TIME		:= $(shell date +%y%m%d-%H%M%S)
RSTDIR		= result-$(now)
PRGNAME		= program-$(now)

CPPFLAGS = $(addprefix -I , $(include_subdir))
# vpath %.cpp src
# vpath %.hpp include
# vpath %.o	obj
VPATH = src include obj $(include_subdir) $(src_subdir)

## Target
EXE := VEM.exe
TARGET := $(BINDIR)/$(EXE)
#OUTOBJ   = $(addprefix $(object_dir)/, $(addsuffix .o, $(notdir $(basename $(INCLUDE)))))
OUTOBJ = $(addprefix $(object_dir)/, $(OBJS))

.PHONY: target all run gene clean test stat open

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
	@$(COLORECH)
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

stat:
	@$(COLORECHO) -I$(INCDIR)
	@$(PRINT) -n '==> Generating...'
	@$(CLRECHO)
	@[ -d $(stat_dir) ] || $(MKDIR) $(stat_dir)
	@cd $(BINDIR); $(PY) ../script/stat.py
	@cd $(stat_dir); $(PLOT) auto.plt 1>/dev/null 2>/dev/null
	@$(PRINT) 'done'

open:
	@$(COLORECHO)
	@$(PRINT) '==> Open'
	@$(CLRECHO)
	@open stat/index.html

test:
	@cd $(test_dir); $(MAKE) -f $(test_make_name)

all: $(TARGET) run stat tail

# Dependencies #################################################################
$(object_dir)/main.o: Human.hpp Virus.hpp Config.hpp Function.hpp Tcell.hpp

$(object_dir)/Human.o: Human.hpp Gene.hpp Virus.hpp Cell.hpp Mobile.hpp Landscape.hpp Host.hpp Tcell.hpp
$(object_dir)/Config.o: Config.hpp
$(object_dir)/Gene.o: Gene.hpp
$(object_dir)/Cell.o: Cell.hpp Function.hpp Virus.hpp Host.hpp
$(object_dir)/Virus.o: Virus.hpp Gene.hpp
$(object_dir)/Tcell.o: Tcell.hpp Gene.hpp Mobile.hpp

$(object_dir)/Host.o: Host.hpp Virus.hpp

$(object_dir)/HumanCounter.o: HumanCounter.hpp
$(object_dir)/VirusCounter.o: VirusCounter.hpp

$(object_dir)/Term.o: Term.hpp
$(object_dir)/FileFactory.o: FileFactory.hpp Term.hpp Function.hpp
$(object_dir)/Function.o: Function.hpp Random.hpp
################################################################################
