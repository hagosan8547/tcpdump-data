# v0.0.0 "Using libpcap in C"

ifeq ($(OS),Windows_NT)
PCAP_LIB = -lwpcap
else
PCAP_LIB = -lpcap
endif

SUFFIX   = .c

SRCDIR   = ./src
INCLUDE  = ./include

COMPILER = gcc
CLIB     = $(PCAP_LIB)

SOURCES  = $(wildcard $(SRCDIR)/*$(SUFFIX))
OBJECTS  = $(notdir $(SOURCES:$(SUFFIX)=.o))
TARGETS  = $(notdir $(basename $(SOURCES)))

CFLAGS  += -Wall -O2

PROGRAM  = tcpdump-data

ifeq ($(OS),Windows_NT)
CLIB +=  -lwsock32 -lws2_32
endif

.PHONY: all
all: obj-make exe-make
	@rm $(OBJECTS)

.PHONY: obj-make
obj-make: $(OBJECTS)
$(OBJECTS): $(SOURCES)
	$(COMPILER) -I$(INCLUDE) $(CFLAGS) -c $+ $(CLIB)

.PHONY: exe-make
exe-make: $(PROGRAM)
$(PROGRAM): $(OBJECTS)
	$(COMPILER) -I$(INCLUDE) $(CFLAGS) -o $@ $^ $(CLIB)

.PHONY: debug
debug:
	@echo "$(TARGETS)"
	@echo "$(OBJECTS)"
	@echo "$(SOURCES)"

.PHONY: find-dir
find-dir:
	@echo "Non\n"

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(addprefix $(EXEDIR)/,$(TARGETS))
