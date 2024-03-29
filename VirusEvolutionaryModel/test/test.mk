
## Command
CC                = g++ -Wall -g -O0 #-std=c++11
PRINT             = echo
MKDIR             = mkdir -vp
MAKE              = make --no-print-directory -s
COPY              = cp
RM                = rm -rfv
TAIL              = tail

## Colors
BOLDECHO          = printf '\033[1m'
REVERSEECHO       = printf '\033[7m'
REDECHO           = printf '\033[31m'
GREENECHO         = printf '\033[32m'
YELLOWECHO        = printf '\033[33m'
BLUEECHO          = printf '\033[34m'
CLRECHO           = printf '\033[0m\033[39m'
COLORECHO         = $(BOLDECHO); $(BLUEECHO)


.PHONY: all

all:
	@$(COLORECHO)
	@$(PRINT) '==> test program'
	@$(CLRECHO)

