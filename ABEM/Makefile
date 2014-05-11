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
OBJS     := $(addprefix $(OBJDIR), $(shell ls obj))


.PHONY: all $(TARGET) $(LIBSPATH)

all: $(TARGET)

$(TARGET): $(LIBSPATH)
	$(CC) -o $@ $(OBJS)

$(LIBSPATH):
	@$(MAKE) -C $@
