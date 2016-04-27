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
ROOT = ../../../..
include $(ROOT)/global.mk
-include colorizer.mk
-include *.dep

.SUFFIXES:

OBJECTS :=  \
	main-nmc.o \
	easyconf.o \
	aura-exports.o

TARGET=rpc-demo

NMCPP_FLAGS     = -DNEURO -OPT2 -inline 
NMCC_FLAGS      = -nmc3 -DNEURO -O2 -Snolink
ASM_FLAGS       = -soc -Snolink -X-q 
BUILDER_FLAGS	= -cK1879.cfg -m -heap=4000 -heap1=6384 -heap2=6384 -heap3=6384 -stack=2000 -full_names

INC_DIRS        = -I. -I"$(NEURO)/include" -I"$(NMPP)/include" -I"$(EASYNMC)/include"
LIB_DIRS		= -L"$(NEURO)/lib" -L"$(EASYNMC)" -L$(NMPP)/lib

#BIG FAT WARNING: easynmc.lib MUST go BEFORE libc
#BIG FAT WARNING: Otherwise argc/argv won't work 
LIBS            = easynmc.lib libc05.lib nmpp-nmc3.lib  libint_soc.lib nmpp-nmc3-rpc.lib

.DEFAULT_GOAL=all

all:   $(TARGET).abs

.PHONY libs: $(LIBS)

%.o: %.c
	$(SILENT_DEP)$(CROSS_COMPILE)gcc -E -MM $(<) -o$(@).dep $(INC_DIRS) 
	$(SILENT_NMCC)nmcc -Tc99 $(NMCC_FLAGS) $(<) -o$(@) $(INC_DIRS) 

%.o: %.asm
	$(SILENT_NMCC)nmcc $(ASM_FLAGS) $(<) -o$(@) $(INC_DIRS)

$(TARGET).abs: $(OBJECTS) $(EASYNMC)/easynmc.lib
	$(SILENT_LINKER)linker  $(BUILDER_FLAGS) -o$(@) $(OBJECTS) $(LIBS) $(LIB_DIRS)

$(TARGET).dump: $(TARGET).abs
	$(SILENT_NMDUMP)nmdump -f $(^) > $(@)

clean:
	-$(OS_RM) *.o $(TARGET).abs $(TARGET).dump *.dep *.ac *.map *~ *.abs *.lib *.asmx


$(EASYNMC)/easynmc.lib:
	$(MAKE) -C $(EASYNMC)
	
$(NMPP)/lib/nmpp-nmc3.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3
	
$(NMPP)/lib/nmpp-nmc3-rpc.lib:
	$(MAKE) -C $(NMPP)/make/nmpp-nmc3-rpc
	