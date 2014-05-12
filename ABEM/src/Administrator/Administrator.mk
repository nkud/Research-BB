CC       = g++
PRINT    = /bin/echo
MKDIR	 = mkdir -vp

OBJDIR = ../../obj
INCLUDE = ../../include

vpath %.h $(INCLUDE)
vpath %.h $(INCLUDE)/AdministratorStrategy
vpath %.cpp AdministratorStrategy

TARGET	 = Administrator.o AdministratorStrategy.o NonOverlappingStrategy.o

CPPFLAGS = -I ../../include


OBJS = $(addprefix $(OBJDIR)/, $(TARGET))

all: $(OBJS)

$(OBJDIR)/%.o: %.cpp
	@$(PRINT) Compiling $(notdir $@)...
	@[ -d $(OBJDIR) ] || $(MKDIR) $(OBJDIR)
	@$(CC) -c $< -o $@ $(CPPFLAGS)

$(OBJDIR)/Administrator.o:  Global.h Function.h Administrator.h Agent.h Virus.h Landscape.h Monitor.h
$(OBJDIR)/AdministratorStrategy.o: Administrator.h Landscape.h Agent.h AdministratorStrategy.h Monitor.h Function.h
