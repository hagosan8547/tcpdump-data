# v0.0.0 "Using libpcap in C"

SUFFIX   = .c

SRCDIR   = ./src
INCLUDE  = ./include
EXEDIR   = ./bin

COMPILER = gcc
CLIB     = -lpcap

SOURCES  = $(wildcard $(SRCDIR)/*$(SUFFIX))
OBJECTS  = $(notdir $(SOURCES:$(SUFFIX)=.o))
TARGETS  = $(notdir $(basename $(SOURCES)))

CFLAGS  += -Wall -O2

PROGRAM  = tcpdump-data

.PHONY: all
all: obj-make exe-make
	@rm $(OBJECTS)

.PHONY: obj-make
obj-make: $(OBJECTS)
$(OBJECTS): $(SOURCES)
	$(COMPILER) -I$(INCLUDE) $(CFLAGS) -c $+

.PHONY: exe-make
exe-make: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(COMPILER) -I$(INCLUDE) $(CFLAGS) -o $(EXEDIR)/$@ $^ $(CLIB)

.PHONY: debug
debug:
	@echo "$(TARGETS)"
	@echo "$(OBJECTS)"
	@echo "$(SOURCES)"

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(addprefix $(EXEDIR)/,$(TARGETS))
