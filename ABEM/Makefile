CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp
MAKE = make

OBJDIR = obj/
SRCDIR = src/
BINDIR = bin/

VPATH = obj

TARGET	 = 

CPPFLAGS = -I include

LIBS := Agent Virus Landscape Administrator TagInterface Function \
		Monitor FileFactory Main Benchmark
TARGET := ABEM.out

LIBSPATH := $(addprefix $(SRCDIR), $(LIBS))
OBJS     = $(addprefix $(OBJDIR), $(shell ls obj))

.PHONY: all run gene $(BINDIR)$(TARGET) $(LIBSPATH)


$(BINDIR)$(TARGET): $(LIBSPATH)
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CC) -o $@ $(OBJS)

$(LIBSPATH):
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	@$(MAKE) -C $@ -f makefilea

run:
	@$(PRINT) '[ run ]'
	@cd $(BINDIR); ./$(TARGET)

gene:
	@$(PRINT) '[ generate ]'
	@cd $(BINDIR); python ../script/gene.py
	@-cd $(BINDIR); gnuplot auto.plt

clean:
	@$(PRINT) [ clean ]
	@$(RM) -rvf $(OBJDIR) $(BINDIR)

check:
	@$(PRINT) [ check ]
	@$(PRINT) there is no test.

all: $(BINDIR)$(TARGET) run gene

