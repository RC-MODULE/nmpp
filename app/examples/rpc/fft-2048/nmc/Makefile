#
# This is a basic Makefile template for a Neuromatrix DSP project 
# to be run on Module MB77.07. To compile it you need: 
# * Latest NMSDK installed with utilities in your $PATH
# * NEURO environment variable pointing to NMSDK directory
# * Host GCC (Since nmcpp doesn't support generating deps, 
#	       we use $(CROSS_COMPILE)gcc for that) 
#
# To disable colorizer run 'make VERBOSE=y'
#
ROOT = ../../../../..
include $(ROOT)/global.mk
#-include colorizer.mk
#-include *.dep

.SUFFIXES:

OBJECTS :=  \
	main-nmc.o \
	easyconf.o \
	aura-exports.o

TARGET=rpc-demo

NMCPP_FLAGS     = -soc -DNEURO -OPT2 -inline 
NMCC_FLAGS      = -soc -DNEURO -O2 -Snolink
ASM_FLAGS       = -soc -Snolink -X-q 
BUILDER_FLAGS	= -cK1879.cfg -m  -heap=0 -heap1=0  -heap2=0 -heap3=0 -stack=2000 -full_names

INC_DIRS        = -I. -I"$(NEURO)/include" -I"$(NMPP)/include" -I"$(EASYNMC)/include"
$(info $(INC_DIRS))
LIB_DIRS		= -L"$(NEURO)/lib" -L"$(EASYNMC)" -L$(NMPP)/lib

-include = nulheap.mk
LAST_SEGMENT := $(shell  printf '%d' $(SEGMENT))
LAST_SIZE    := $(shell  printf '%d' $(SIZE))
MEMORY_SIZE  := $(shell  printf '%d' 0x00020000)
HEAP_SIZE=$(shell expr $(MEMORY_SIZE) - $(LAST_SEGMENT) - $(LAST_SIZE) - 8 )
#$(info LAST_SEGMENT=$(LAST_SEGMENT))
#$(info LAST_SIZE=$(LAST_SIZE))
#$(info MEMORY_SIZE=$(MEMORY_SIZE))
$(info INFORMATION: $(HEAP_SIZE) of internal memory is unused  )

	
#BIG FAT WARNING: easynmc.lib MUST go BEFORE libc
#BIG FAT WARNING: Otherwise argc/argv won't work 
LIBS            = easynmc.lib nmpp-nmc3.lib  libint_soc.lib libc05.lib  nmpp-nmc3-rpc.lib 

.DEFAULT_GOAL= build


all:   $(TARGET).abs

libs: $(LIBS)

aura-exports.o: $(ROOT)/include/rpc/aura-exports.c
	$(SILENT_NMCC)nmcc -Tc99 $(NMCC_FLAGS) $(<) -o$(@) $(INC_DIRS) 

%.o: %.c aura-exports.h
	$(SILENT_DEP)$(CROSS_COMPILE)gcc -E -MM $(<) -o$(@).dep $(INC_DIRS) 
	$(SILENT_NMCC)nmcc -Tc99 $(NMCC_FLAGS) $(<) -o$(@) $(INC_DIRS) 


%.o: %.asm
	$(SILENT_NMCC)nmcc $(ASM_FLAGS) $(<) -o$(@) $(INC_DIRS)


#nulheap.abs: $(OBJECTS) $(EASYNMC)/easynmc.lib $(ROOT)/lib/nmpp-nmc3-rpc.lib $(ROOT)/lib/nmpp-nmc3.lib K1879.cfg Makefile
nulheap.abs: $(OBJECTS) $(EASYNMC)/easynmc.lib $(ROOT)/lib/nmpp-nmc3-rpc.lib $(ROOT)/lib/nmpp-nmc3.lib K1879.cfg Makefile
	@echo ----- FIRST PASS BUILD ---------
	$(SILENT_LINKER)linker  $(BUILDER_FLAGS) -onulheap.abs $(OBJECTS) $(LIBS) $(LIB_DIRS)
	@echo SEGMENT= \> ./nulheap.mk
	@grep SEGMENT     ./nulheap.map | tail -1 | cut -d " " -d "," -f2 | cut -d ":" -f2 >> nulheap.mk
	@echo SIZE = \>>  ./nulheap.mk
	@grep SEGMENT     ./nulheap.map | tail -1 | cut -d " " -d "," -f3 | cut -d ":" -f2 >> nulheap.mk
	

rpc-demo.abs: $(OBJECTS) $(EASYNMC)/easynmc.lib $(ROOT)/lib/nmpp-nmc3-rpc.lib $(ROOT)/lib/nmpp-nmc3.lib K1879.cfg Makefile
	@echo ----- SECOND PASS BUILD ---------
	$(SILENT_LINKER)linker  -heap=$(HEAP_SIZE) $(BUILDER_FLAGS)  -o$(TARGET).abs $(OBJECTS) $(LIBS) $(LIB_DIRS)

build:	
	$(MAKE) -C . nulheap.abs	
	$(MAKE) -C . rpc-demo.abs	
	
#	$(SILENT_LINKER)linker $(HEAP_SIZE) -heap=131070 $(BUILDER_FLAGS)  -o$(TARGET).abs $(OBJECTS) $(LIBS) $(LIB_DIRS)	
	

$(TARGET).dump: $(TARGET).abs
	$(SILENT_NMDUMP)nmdump -f $(^) > $(@)

clean:
	-$(OS_RM) *.o $(TARGET).abs $(TARGET).dump *.dep *.ac *.map *~ *.abs *.lib *.asmx nulheap.mk


$(EASYNMC)/easynmc.lib:
	$(MAKE) -C $(EASYNMC) PATH="%path%;$(realpath $(GNUWIN32))"
	
$(NMPP)/lib/nmpp-nmc3.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3
	
$(NMPP)/lib/nmpp-nmc3-rpc.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3-rpc
	