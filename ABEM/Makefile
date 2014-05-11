CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp
MAKE = make

OBJDIR = obj
SRCDIR = src/
BINDIR = bin/

VPATH = obj

TARGET	 = 

CPPFLAGS = -I include

LIBS := Agent Virus Landscape Administrator TagInterface Function \
		Monitor FileFactory Main Benchmark
TARGET := ABEM.out

LIBSPATH := $(addprefix $(SRCDIR), $(LIBS))
OBJS     = $(addprefix $(OBJDIR)/, $(shell ls obj))

.PHONY: all run gene $(BINDIR)$(TARGET) $(LIBSPATH)


$(BINDIR)$(TARGET): $(LIBSPATH)
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJS)

# ライブラリをコンパイルする
# ライブラリ名.mk を使用する
$(LIBSPATH):
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@$(MAKE) -C $@ -f $(notdir $@).mk

# 実行する
run:
	@$(PRINT) '[ run ]'
	@cd $(BINDIR); ./$(TARGET)

# 結果を出力する
gene:
	@$(PRINT) '[ generate ]'
	@cd $(BINDIR); python ../script/gene.py
	@-cd $(BINDIR); gnuplot auto.plt

# 削除する
clean:
	@$(PRINT) [ clean ]
	@$(RM) -rvf $(OBJDIR) $(BINDIR)

# テストする
check:
	@$(PRINT) [ check ]
	@$(PRINT) there is no test.

# コンパイル -> 実行 -> 結果出力
all: $(BINDIR)$(TARGET) run gene

