

#include $(ROOT)/global.mk
	   
PROJECT = test-x64
#TARGET  = $(call OSX,bin/x64/Release/$(PROJECT))

ifeq ($(OS),Windows_NT)
  TARGET  = bin\x64\Release\$(PROJECT)
  .DEFAULT_GOAL := vs2015
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



vs2015:
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild $(PROJECT).vcxproj /p:Configuration=Release /property:Platform=x64
	
vs2005:
	premake5 vs2005	
	"$(VS80COMNTOOLS)vsvars32" && vcbuild $(PROJECT).vcproj

gmake:
	$(CP) Makefile .Makefile.origin
	premake5 gmake2 --verbose
	$(CP) Makefile .Makefile.premake
	$(CP) .Makefile.origin Makefile
	$(MAKE) -f .Makefile.premake test-x64 verbose=y config=release_x64
	
	
	
.PHONY: run 
	
run:	
	$(TARGET)
	
test: .exitcode
	
.exitcode: $(TARGET) .test.bat
	.test.bat 
	
.test.bat: 
	@echo $(TARGET) >.test.bat
	@echo @echo %%errorlevel%% ^>.exitcode >>.test.bat



	
	
	
include $(ROOT)/clean.mk	