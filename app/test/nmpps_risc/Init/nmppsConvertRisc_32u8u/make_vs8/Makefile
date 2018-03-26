ROOT=../../../../../..
include $(ROOT)/global.mk
# This makefile builds simple win32-application containing single cpp-file  
# Rule 'run' executes the application under Windows OS and stores return code in ".exitcode"  file

.SUFFIXES:

#NMPP?=

ifndef VS80COMNTOOLS
$(warning *** WARNING: 'VS80COMNTOOLS' environment variable is not defined! Microsoft Visual Studio 8  might not have installed correctly. )
.DEFAULT_GOAL := skip
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
LIBS             =nmpp-x86.lib 
RUN_COMMAND      =$(TARGET)
#--------------  DEBUG config -------------------------
TMP_DIRD         =Debug
TARGETD          =$(TMP_DIRD)\$(PROJECT)d.exe
LIBSD            =nmpp-x86.lib
RUND_COMMAND     =$(TARGETD)
#--------------  Visual Studio config (for vs8.mk)--
HEADER_DIRS      =$(NMPP)/nmplv/include
RESOURCES        =Makefile

# regular search of *.c *.cpp,*.asm sources in all $(SRC_DIRS)
ALL_CPP =$(wildcard $(addsuffix /*.cpp,$(SRC_DIRS)))
ALL_C   =$(wildcard $(addsuffix /*.c,$(SRC_DIRS)))
ALL_H   =$(wildcard $(addsuffix /*.h,$(HEADER_DIRS)))
#======================== BUILD RULES ====================================


.PHONY: run clean 

VPATH    = $(subst -l,,$(LIB_DIRS)) 

$(TARGETD): $(PROJECT).vcproj $(ALL_CPP) $(NMPP)/lib/$(LIBSD)
	rm -f -r $(@)
	@echo $(CURDIR)>> $(ROOT)/app/test/build-vs8.txt
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj
	@echo -OK>> $(ROOT)/app/test/build-vs8.txt

run:	$(TARGETD)
	$(TARGETD)

test: .exitcode
	

.exitcode: $(TARGETD) .test.bat
	.test.bat 
	
.test.bat: 
	@echo $(TARGETD) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat

clean:
	-$(OS_RM) -f -r .* *.o *.ncb *.ilk $(TARGET) $(TARGETD) *.dep *.ac *.map *.suo *.ncb *.user null
	-$(OS_RD) $(TMP_DIR) $(TMP_DIRD)
	
export HEADER_DIRS
export INC_DIRS LIB_DIRS
export LIBS LIBSD
export ALL_CPP ALL_ASM ALL_C ALL_H
export TARGET TARGETD
	
vs8: $(PROJECT).vcproj

$(PROJECT).vcproj: Makefile
	make --file=$(NMPP)/deps/projector/vs8.mk vc-app --silent >$(@)

	
skip:
	@echo Compilation is skipped!
	

