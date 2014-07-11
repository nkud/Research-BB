HOME	 = ~/workspace/AgentBasedEpidemicModel/ABEM

CC       = g++ -Wall -g -O0 -std=c++11
PRINT    = /bin/echo
MKDIR	 = mkdir -p
MAKE	 = make --no-print-directory -s
COPY	 = cp
CTAGS	 = $(shell which ctags)

SRC		 = $(shell find src -name '*.cpp')
INCLUDE  = $(shell find include -name '*.h' -or -name '*.hpp')

OBJDIR	 = obj
SRCDIR	 = src
BINDIR	 = bin
PRGDIR	 = program

MASTER	 = master
AGENTDIR	 = AgentDataBase
VIRUSDIR	 = VirusDataBase

NOW		 := $(shell date +%y%m%d-%H%M%S)
RESULT   = result-$(NOW)
PROGRAM  = program-$(NOW)

VPATH = obj include

LIBS := $(shell ls $(SRCDIR))

LIBSPATH := $(addprefix $(SRCDIR)/, $(LIBS))
OBJS     = $(addprefix $(OBJDIR)/, $(shell ls obj))

TARGET := ABEM.out

R = notitle

.PHONY: all run gene $(BINDIR)/$(TARGET) $(LIBSPATH)


# ターゲットを作成する
$(BINDIR)/$(TARGET): $(LIBSPATH)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	@$(PRINT) -n '===> $(notdir $@)...'
	@$(CC) -o $@ $(OBJS)
	@$(PRINT) 'Done. ( success compiling )'

# コンパイルする
# Makefile名とフォルダ名は同じにする
$(LIBSPATH):
	@printf '\033[31m'
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(PRINT) '---> $(notdir $@)'
	@printf '\033[39m'
	@$(MAKE) -C $@ -f $(notdir $@).mk
	@$(PRINT)

### テスト
test:
	# $(MAKE) -C -f $(notdir $@).mk test

# 実行する
run:
	@$(PRINT) '[ run ]'
	@$(RM) $(BINDIR)/*.txt
	@[ -d $(BINDIR)/$(AGENTDIR) ] || $(MKDIR) $(BINDIR)/$(AGENTDIR)
	@[ -d $(BINDIR)/$(VIRUSDIR) ] || $(MKDIR) $(BINDIR)/$(VIRUSDIR)
	@$(RM) $(BINDIR)/$(AGENTDIR)/*.txt
	@$(RM) $(BINDIR)/$(VIRUSDIR)/*.txt
	@cd $(BINDIR); ./$(TARGET)

# 結果を出力する
gene:
	@$(PRINT) '>>> Generating...'

	@-cd $(BINDIR); python ../script/gene.py
	@-cd $(BINDIR); gnuplot auto.plt 1>/dev/null
	# @cd $(BINDIR)/$(VIRUSDIR); gnuplot vvd.plt 1>/dev/null
	# @cd $(BINDIR)/$(AGENTDIR); gnuplot avd.plt 1>/dev/null
	@-cd $(BINDIR)/$(AGENTDIR); gnuplot animation.plt >/dev/null 2>&1
	@-cd $(BINDIR)/$(VIRUSDIR); gnuplot animation.plt >/dev/null 2>&1


# 結果をパッケージングする
pack:
	@$(PRINT) '>>> Packaging'
	@$(PRINT) FNAME:[ $(RESULT)-$(R) ]
	@[ -d $(MASTER) ] || $(MKDIR) $(MASTER)
	@[ -d $(MASTER)/$(RESULT)-$(R)/$(PRGDIR) ] || $(MKDIR) $(MASTER)/$(RESULT)-$(R)/$(PRGDIR)
	@cp -r bin/* $(MASTER)/$(RESULT)-$(R)
	@cp -r Makefile include src script $(MASTER)/$(RESULT)-$(R)/$(PRGDIR)
	@cp -r html $(MASTER)/$(RESULT)-$(R)
	#@cd $(MASTER)/$(RESULT)-$(R); ln -s html/index.html document.html
	@ls $(MASTER)/$(RESULT)-$(R)

archive:
	@python script/archive.py

doc: $(SRC)
	@$(PRINT) '>>> create Documents'
	@doxygen 2>/dev/null 1>/dev/null

ext:
	@$(PRINT) '>>> Extraction'
	@$(PRINT) FNAME:[ $(PROGRAM) ]
	@[ -d $(PROGRAM) ] || $(MKDIR) $(PROGRAM)
	@[ -d $(PROGRAM)/src ] || $(MKDIR) $(PROGRAM)/src
	@[ -d $(PROGRAM)/include ] || $(MKDIR) $(PROGRAM)/include
	@-find src -name '*.cpp' -exec cp {} $(PROGRAM)/src/ \;
	@-find include -name '*.h' -exec cp {} $(PROGRAM)/include \;
	@-find include -name '*.hpp' -exec cp {} $(PROGRAM)/include \;

# 削除する
clean:
	@$(PRINT) -n '>>> Cleaning...'
	@$(RM) -vrf $(OBJDIR) $(BINDIR)
	@$(PRINT) 'done'

# テストする
check:
	@$(PRINT) [ check ]
	@$(PRINT) there is no test.

print:
	@$(PRINT) [ print ]

grep:
	@$(PRINT) '>>> src files'
	@-find src -name '*.cpp' | xargs grep $(G) --color
	@$(PRINT) '>>> include files'
	@-find include -name '*.h' | xargs grep $(G) --color
	@$(PRINT) '>>> makefile files'
	@-grep $(G) Makefile --color
	@-find src -name '*.mk' | xargs grep $(G) --color

tags:
	@$(PRINT) '>>> ctag'
	@find src -name '*.cpp' | xargs $(CTAGS)

mail:
	@$(PRINT) '>>> mail'
	@-cd $(BINDIR); python ../script/mail.py $(NOW)

test:

# コンパイル -> 実行 -> 結果出力
all: $(BINDIR)/$(TARGET) run gene

build: clean $(BINDIR)/$(TARGET)
