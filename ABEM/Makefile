CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp
MAKE 	 = make -k

OBJDIR = obj
SRCDIR = src
BINDIR = bin

VPATH = obj

CPPFLAGS = -I include

LIBS := $(shell ls $(SRCDIR))

LIBSPATH := $(addprefix $(SRCDIR)/, $(LIBS))
OBJS     = $(addprefix $(OBJDIR)/, $(shell ls obj))

TARGET := ABEM.out

.PHONY: all run gene $(BINDIR)/$(TARGET) $(LIBSPATH)


# ターゲットを作成する
$(BINDIR)/$(TARGET): $(LIBSPATH)
	@[ -d $(BINDIR) ] || $(MKDIR) $(BINDIR)
	$(CC) -o $@ $(OBJS)

# コンパイルする
$(LIBSPATH):
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
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

