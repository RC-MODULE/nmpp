# Latest premake  https://premake.github.io/
ROOT             = ../..
include          $(ROOT)/global.mk
VS8       = Visual_Studio_8_2005
VS12      = Visual_Studio_12_2013
VS12X64   = Visual_Studio_12_2013_Win64
VS14      = Visual_Studio_14_2014
VS14X64   = Visual_Studio_14_2014_Win64
VS15X64   = Visual_Studio_15_2017_Win64
MINGW     = d:/SDK/MinGW

.PHONY: mingw unix;

ifeq ($(OS),Windows_NT)
  SHELL = cmd
  WHICH = where
  RMALL = del /Q /A:A                  
  RMDIR = rmdir /Q /S
  MKDIR = mkdir  
  CPDIR = xcopy /e /y
  CP    = copy                
  MV    = move                 
  ECHO  = echo  
  define OSX
	$(subst /,\,$(1))
  endef  
  export CC = gcc
else
  WHICH = which
  RMALL = rm -f                 
  RMDIR = rm -fr               
  MKDIR = mkdir -p             
  CPDIR = cp -r                
  CP    = cp                   
  MV    = mv                   
  ECHO  = echo    
  define OSX
	$(subst \,/,$(1))
  endef  
endif
#	$(CP)		$(call OSX,$(VS8)/Debug/*.lib) 	$(call OSX,../../lib/)
#	$(CP)  		$(call OSX,$(VS8)/Release/*.lib) $(call OSX,../../lib/)

PROJECT = nmpp
all: vs2015
	$(VS14X64) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp-x64.vcxproj /p:Configuration=Release
	
configure-mingw MinGW/Makefile:
	-$(RMDIR)   MinGW	
	$(MKDIR) 	MinGW
	cd    		MinGW && cmake .. -G "MinGW Makefiles"
#	cd    		MinGW && set path=$(MINGW)/bin;$(PATH) &&	cmake .. -G "MinGW Makefiles" 

mingw: MinGW/Makefile
	$(MAKE) -C MinGW 
	
configure-unix Unix/Makefile:     
	-$(RMDIR)   Unix	
	$(MKDIR)    Unix
	cd          Unix &&  cmake .. -G "Unix Makefiles" 
#	cd          Unix &&  set path=$(MINGW)/bin;$(PATH) && cmake .. -G "Unix Makefiles" -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	
unix: Unix/Makefile
	$(MAKE) -C Unix
#	-DCMAKE_C_COMPILER="d:/SDK/MinGW/bin/gcc" -DCMAKE_CXX_COMPILER="d:/SDK/MinGW/bin/g++"  -DCMAKE_MAKE_PROGRAM="d:/SDK/MinGW/bin/mingw32-make" 



gmake:
	$(CP) Makefile .Makefile.origin
	premake5 gmake
	$(CP) Makefile .Makefile.premake
	$(CP) .Makefile.origin Makefile
	$(MAKE) -f .Makefile.premake nmpp
	
vs2005:    	
	premake5 vs2005
	"$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.sln  "Release|Win32"
	"$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.sln  "Debug|Win32"
	"$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.sln  "Release|x64"
	"$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.sln  "Debug|x64"

vs2015:
	premake5 vs2015
	"$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=win32
	"$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=win32
	"$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=x64
	"$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=x64
	
vs2017:
	premake5 vs2017
    "$(VS150COMNTOOLS)VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=win32
    "$(VS150COMNTOOLS)VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=win32
    "$(VS150COMNTOOLS)VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=x64
    "$(VS150COMNTOOLS)VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=x64

include $(ROOT)/clean.mk
	