#
# Virus Evolutionary Model Makefile
#
#		Author: Naoki Ueda
# Organization: OPU
#

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
SED	  = sed

## Directory Names
src_files            = $(shell find src -name '*.cpp')
include_files        = $(shell find include -name '*.h' -or -name '*.hpp')
output_files = $(shell find bin -name '*.txt')

object_dir     = obj

src_dir         = src
include_dir         = include
include_subdirs = $(shell find $(include_dir) -type d)
src_subdirs = $(shell find $(src_dir) -type d)

depend = depend

script_dir         = script
bin_dir         = bin
PRGDIR         = program
master_dir         = master

test_dir       = test
stat_dir       = stat
test_make_name = test.mk

clean_directory = $(bin_dir) $(object_dir) $(stat_dir)
bin_clean_files = $(output_files)
test_make_file	= $(test_dir)/$(test_make_name)

now			= $(shell date +%y%m%d-%H%M%S)
timestamp	:= $(shell date '+< %y/%m/%d %H:%M:%S >')
TIME		:= $(shell date +%y%m%d-%H%M%S)
RSTDIR		= result-$(now)
PRGNAME		= program-$(now)

CPPFLAGS = $(addprefix -I , $(include_subdirs))
# vpath %.cpp src
# vpath %.hpp include
# vpath %.o	obj

VPATH = src include obj $(include_subdirs) $(src_subdirs)

## Target
EXE := VEM.exe
TARGET := $(bin_dir)/$(EXE)
objects = $(notdir $(subst .cpp,.o,$(src_files)))
OUTOBJ = $(addprefix $(object_dir)/, $(objects))

.PHONY: target all run gene clean bclean test stat open

## Make Program
$(TARGET): $(OUTOBJ)
	@$(COLORECHO)
	@$(PRINT) -n '==> Linking $(notdir $@)...'
	@$(CLRECHO)
	@[ -d $(bin_dir) ] || $(MKDIR) $(bin_dir)
	@$(CC) $^ -o $@ $(CPPFLAGS)
	@$(PRINT) 'ok'

depend: $(src_files)
	@$(COLORECHO)
	@$(PRINT) -n '==> Generating $(depend)...'
	@$(CLRECHO)
	@$(CC) -M $(CPPFLAGS) $^ | \
	  $(SED) -e 's,\(^.*\.o\),$(object_dir)/\1,g' > $(depend)
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
	@cd $(bin_dir); ./$(EXE)
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
	tript_dire $(include_dir) $(src_dir) $(object_dir) $(bin_dir) $(scre)

time:
	@$(COLORECH)
	@$(PRINT) '==> $(now)'
	@$(CLRECHO)

bclean:
	@$(COLORECHO)
	@$(PRINT) '==> Cleanning $(bin_clean_files)'
	@$(CLRECHO)
	@$(RM) $(bin_clean_files)

tail:
	@$(COLORECHO)
	@$(PRINT) '==> Log tail'
	@$(CLRECHO)
	@cd $(bin_dir); $(TAIL) log.txt

re: clean $(TARGET)

stat:
	@$(COLORECHO) -I$(include_dir)
	@$(PRINT) -n '==> Generating...'
	@$(CLRECHO)
	@[ -d $(stat_dir) ] || $(MKDIR) $(stat_dir)
	@cd $(stat_dir); $(PY) ../script/stat.py
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

-include $(depend)
-include colors.mk
