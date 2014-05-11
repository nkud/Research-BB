CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp
MAKE 	 = make -k
COPY	 = cp

OBJDIR	 = obj
SRCDIR	 = src
BINDIR	 = bin

MASTER	 = master
NOW		 = $(shell date +"%y_%m%d_%H%M%S")

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
	@$(PRINT) -n 'Generating $(notdir $@)...'
	@$(CC) -o $@ $(OBJS)
	@$(PRINT) 'Done.'

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

# 結果をパッケージングする
pack:
	@$(PRINT) [ package ]
	@[ -d $(MASTER) ] || $(MKDIR) $(MASTER)
	@cd $(MASTER); $(MKDIR) $(NOW)/src
	@cd $(MASTER); $(MKDIR) $(NOW)/assets
	@cd $(MASTER); $(MKDIR) $(NOW)/script
	@-$(COPY) $(BINDIR)/*.txt $(MASTER)/$(NOW)/assets
	@-$(COPY) $(BINDIR)/*.plt $(MASTER)/$(NOW)/script
	@-$(COPY) $(BINDIR)/index.html template/result.css $(MASTER)/$(NOW)
	@tree $(MASTER)/$(NOW)

# 削除する
clean:
	@$(PRINT) [ clean ]
	@$(RM) -rvf $(OBJDIR) $(BINDIR)

# テストする
check:
	@$(PRINT) [ check ]
	@$(PRINT) there is no test.

# コンパイル -> 実行 -> 結果出力
all: $(BINDIR)/$(TARGET) run gene

