include $(ROOT)/setenv.mk
# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file

.SUFFIXES:

NMPP?=

ifndef VS120COMNTOOLS
$(warning *** WARNING: 'VS120COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 13  might not have installed correctly. )
.DEFAULT_GOAL := skip
endif 

ifeq ($(OS),Windows_NT)
  SHELL = cmd
endif

ifndef NMPP
$(error *** ERROR: 'NMPP' environment variable is not defined!  )
endif 

#--------------  target & input dirs -------------------
PROJECT          =main
SRC_DIRS         = .. 
INC_DIRS         =-I"$(NMPP)/include"
LIB_DIRS         =-L"$(NMPP)/lib"  
#--------------  RELEASE/ALL config -------------------
TMP_DIR          =Release
TARGET           =$(TMP_DIR)\$(PROJECT).exe
LIBS             =vs13.lib 
RUN_COMMAND      =$(TARGET)
#--------------  DEBUG config -------------------------
TMP_DIRD         =Debug
TARGETD          =$(TMP_DIRD)\$(PROJECT).exe
LIBSD            =vs13d.lib
RUND_COMMAND     =$(TARGETD)
#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      =$(NMPP)/nmplv/include
RESOURCES        =Makefile

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))


#======================== BUILD RULES ====================================


.PHONY: run clean vs13

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcxproj $(ALL_CPP) $(NMPP)/lib/$(LIBSD)
	rm -f -r $(@)
	"$(VS120COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj

run: .exitcode
	

.exitcode: $(TARGETD) .exitrun.bat
	.exitrun.bat 
	
.exitrun.bat: 
	@echo $(TARGETD) >.exitrun.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.exitrun.bat

clean:
	-rm -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.sdf *.htm *.user $(TMP_DIR) $(TMP_DIRD)
	
export HEADER_DIRS
export INC_DIRS LIB_DIRS
export LIBS LIBSD
export ALL_CPP ALL_ASM ALL_C ALL_H
export TARGET TARGETD
	
vs13: $(PROJECT).vcxproj

$(PROJECT).vcxproj: Makefile
	make --file=$(NMPP)/deps/projector/vs13.mk vc-app --silent >$(@)

	
skip:
	@echo Compilation is skipped!
	

