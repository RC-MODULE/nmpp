#
# This is a universal Makefile for NeuroMatrix projects (application or library) [EDITION 20]
# with automatic recursive search of source files , compiling and linking.
# Makefile is processed by GNU make and may be used both in Linux and Windows OS
#
# To compile it you need: 
# * Latest NMSDK installed with utilities in your $PATH
# * NEURO environment variable pointing to NMSDK directory
# * Host GCC (Since nmcpp doesn't support generating header dependences, we use gcc for that) 
#
# Under OS Windows you need:
# * GNU Make           http://gnuwin32.sourceforge.net/packages/make.htm
# * GNU UNIX utilities http://sourceforge.net/projects/unxutils/ 
#
# USAGE:
#   For release build                    run 'make'
#   For debug   build                    run 'make DEBUG=y'
#   For debug & release  build           run 'make all'
#   For full  rebuild                    run 'make -B'
#   Multithread build (speed up)         run 'make -j4'
#   To clean                             run 'make clean'
#   To clean DEBUG & RELEASE             run 'make cleanall'
#   To create VisualStudio 2005 project  run 'make vs8'
#   For verbose build (no colorizing)    run 'make VERBOSE=y'
#
# WARNING:
#   Makefile is sensitive to leading or trailing spaces and backslashes in the pathes
#
# DEFENITIONS:
#   PROJECT         - project name     
#   TARGET          - output target (.lib or .abs) file with path
#   INC_DIRS        - set of search pathes for the macro libraries and includes (with -I flag separated)
#   SRC_DIRS        - set of explicit  search pathes of all (.c .cpp .asm) source files (with space separated)
#   LIB_DIRS        - set of search library pathes (with -l flag separated)
#   TMP_DIR         - temporary build-folder (Debug/Release)
#   
#   CC              - C/C++ compiler(nmcpp/nmcc)
#   CC_FLAGS        - C/C++ compiler(nmcpp/nmcc) flags   
#   AS				- assembler(asm/nmcc)
#   AS_FLAGS        - assembler(asm/nmcc) flags for compiling of pure .asm files 
#   AS_FLAGS_C2ASM  - assembler(asm/nmcc) flags for compiling of .asm files compiled from .c/.cpp sources
#   BUILDER         - builder  (libr/linker) 			
#   BUILDER_FLAGS   - build flags of (libr/linker)
  
#
#============== PROJECT & BUILD CONFIGURATION ==========
ROOT             = ../..
ifeq ($(OS),Windows_NT)
SHELL 			 = cmd
endif

#include          $(ROOT)/global.mk

ifndef NEURO
$(error *** ERROR: 'NEURO' environment variable is not defined! NMSDK might not have installed correctly. )
endif

ARCH             =nmc4
#--------------  target & input dirs -------------------
include          $(ROOT)/make/src-nmc-float.mk
PROJECT          = nmpp-$(ARCH)f
TMP_DIR          = Release
OUT_DIR          = $(ROOT)/lib
TARGET           = $(OUT_DIR)/$(PROJECT).lib
INC_DIRS         = -I"$(NEURO)/include"  -I$(ROOT)/include


#--------------  RELEASE/ALL config -------------------
AS               =asm 				 
AS_FLAGS         =-$(ARCH) -nm2ms  $(INC_DIRS) -split_sir -W-111 -W-109
AS_FLAGS_C2ASM   =-$(ARCH) -nm2ms  $(INC_DIRS) -split_sir -W-111 -W-109
CC               =nmcpp
CCPP_FLAGS       =-nmc3 -DNEURO -OPT2 -inline 
CC_FLAGS         =$(CCPP_FLAGS) -Tc99
BUILDER          =libr
BUILDER_FLAGS    =-c $(TARGET)
#--------------  DEBUG config -------------------------
ifdef DEBUG      
TARGET           =$(OUT_DIR)/$(PROJECT)d.lib
CCPP_FLAGS       =-nmc3 -DNEURO -OPT0 -inline -debug 
CC_FLAGS         =$(CCPP_FLAGS) -Tc99
LIBS            :=
AS_FLAGS        +=-ga
BUILDER_FLAGS   +=-d0
TMP_DIR          =Debug
endif 
#=================== SOURCE & OBJECTS COLLECTION ===========================
.SUFFIXES:

					
# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_ASM =$(wildcard $(addsuffix /*.asm,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_S   =$(wildcard $(addsuffix /*.s,$(SRC_DIRS)))

ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))

VPATH    = $(SRC_DIRS)

# collecting of objects
OBJECTS_CPP = $(notdir $(patsubst %.cpp,%.o,$(ALL_CPP)))
OBJECTS_ASM = $(notdir $(patsubst %.asm,%.o,$(ALL_ASM)))
OBJECTS_C   = $(notdir $(patsubst %.c,%.o,$(ALL_C)))
OBJECTS_S   = $(notdir $(patsubst %.s,%.o,$(ALL_S)))
OBJECTS     = $(addprefix $(TMP_DIR)/,$(OBJECTS_C) $(OBJECTS_CPP)  $(OBJECTS_ASM) $(OBJECTS_S))


#======================== BUILD RULES ====================================
#.DEFAULT_GOAL=default
#default: 
#	$(MAKE) $(TARGET) -j4

$(TARGET): $(TMP_DIR) $(OUT_DIR) $(OBJECTS) 
	$(info "[Linking...]")
	$(BUILDER) $(BUILDER_FLAGS) $(OBJECTS) 

$(TMP_DIR):
	-mkdir "$(@)"
	
$(OUT_DIR): 
	-mkdir "$(@)"
	
$(TMP_DIR)/%.o: %.asm 
	$(AS) $(AS_FLAGS) $(<) -o$(@) $(ERRECHO)
	
$(TMP_DIR)/%.o: %.s
	$(AS) $(AS_FLAGS) $(<) -o$(@) $(ERRECHO)

$(TMP_DIR)/%.o: $(TMP_DIR)/%.asmx 
	$(AS) $(AS_FLAGS_C2ASM) $(<) -o$(@) $(ERRECHO)

$(TMP_DIR)/%.asmx: %.cpp 
	$(CC) $(CCPP_FLAGS) $(<) -O$(@) $(INC_DIRS)  $(ERRECHO)

$(TMP_DIR)/%.asmx: %.c
	$(CC) $(CC_FLAGS) $(<) -O$(@) $(INC_DIRS) $(ERRECHO)

#.phony: time
#time:
#	powershell -c "Measure-Command { $(MAKE)  -j4 | Out-Default }"	
 
#========================== Visual Studio support ===================
HEADER_DIRS      =$(ROOT)/include $(ROOT)/include/nmplv $(ROOT)/include/nmpli $(ROOT)/include/nmpls $(ROOT)/include/nmplm $(ROOT)/include/nmplc
RESOURCES        =Makefile


#vs2005: Makefile
#	$(MAKE) -f $(ROOT)/deps/projector/vs8.mk nmc-app MAK=$(realpath .)/Makefile --silent >$(PROJECT).vcproj 

#vs2015 : Makefile
#	$(MAKE) -f $(ROOT)/deps/projector/vs13.mk nmc-app MAK=$(realpath .)/Makefile --silent >$(PROJECT).vcxproj

#========================== cleanup ===================
include $(ROOT)/clean.mk
