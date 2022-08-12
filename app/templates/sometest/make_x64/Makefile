


#include $(ROOT)/global.mk
	   
PROJECT = test-x64
#TARGET  = $(call OSX,bin/x64/Release/$(PROJECT))

ifeq ($(OS),Windows_NT)
  TARGET  = bin\x64\Release\$(PROJECT).exe
  #.DEFAULT_GOAL := vs2017
  SHELL = cmd
  OS_RD    = rd /Q /S 
  OS_RM    = del /Q
  OS_CP    = copy
  OS_MKDIR = mkdir  
  export CC = gcc
else
  TARGET  = bin/x64/Release/$(PROJECT)
  .DEFAULT_GOAL := gmake
  OS_RM    = rm -f -r
  OS_RD    = rm -d -r
  OS_CP    = cp
  OS_MKDIR = mkdir -p  
endif

.PHONY: run vs2017 


#$(info ----- $(TARGET))

$(TARGET): ../main.cpp
	premake5 vs2017
	msbuild $(PROJECT).vcxproj /p:Configuration=Release /property:Platform=x64

#FORCE: 

vs2015:
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release /property:Platform=x64

vs2017:
	premake5 vs2017
	"$(VS150COMNTOOLS)VsDevCmd.bat" && msbuild $(PROJECT).vcxproj /p:Configuration=Release /property:Platform=x64
	
vs2005:
	premake5 vs2005	
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

gmake:
	$(OS_CP) Makefile .Makefile.origin
	premake5 gmake2 --verbose
	$(OS_CP) Makefile .Makefile.premake
	$(OS_CP) .Makefile.origin Makefile
	$(MAKE) -f .Makefile.premake test-x64 verbose=y config=release_x64
	
	
	
run: .exitcode
	
		
.exitcode: $(TARGET)
	$(TARGET) & exitcode
 
	

qemu:
	

	
	
include $(ROOT)/clean.mk	