CC       = g++ -Wall
PRINT    = /bin/echo
MKDIR	 = mkdir -p
MAKE 	 = make --no-print-directory -s
COPY	 = cp
CTAGS	 = $(shell which ctags)

OBJDIR	 = obj
SRCDIR	 = src
BINDIR	 = bin

MASTER	 = master
NOW		 = $(shell date +result-%y%m%d-%H%M%S)

VPATH = obj include

LIBS := $(shell ls $(SRCDIR))

LIBSPATH := $(addprefix $(SRCDIR)/, $(LIBS))
OBJS     = $(addprefix $(OBJDIR)/, $(shell ls obj))

TARGET := ABEM.out

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
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(PRINT) '---> $(notdir $@)'
	@$(MAKE) -C $@ -f $(notdir $@).mk
	@$(PRINT)

# 実行する
run:
	@$(PRINT) '[ run ]'
	@$(RM) $(BINDIR)/*.txt
	@cd $(BINDIR); ./$(TARGET)

# 結果を出力する
gene:
	@$(PRINT) '>>> Generating...'
	@cd $(BINDIR); python ../script/gene.py
	@cd $(BINDIR); gnuplot auto.plt

# 結果をパッケージングする
pack:
	@$(PRINT) '>>> Packaging'
	@[ -d $(MASTER) ] || $(MKDIR) $(MASTER)
	@cp -r bin $(MASTER)/$(NOW)
	@tree $(MASTER)/$(NOW)

# 削除する
clean:
	@$(PRINT) -n '>>> Cleaning...'
	@$(RM) -rf $(OBJDIR) $(BINDIR)
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

# コンパイル -> 実行 -> 結果出力
all: $(BINDIR)/$(TARGET) run gene

build: clean $(BINDIR)/$(TARGET)
