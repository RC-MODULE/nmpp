# Latest premake  https://premake.github.io/
ROOT             = ../..

ifeq ($(OS),Windows_NT)
  .DEFAULT_GOAL := vs2015
  SHELL = cmd
  OS_RD    = rd /Q /S 
  OS_RM    = del /Q
  OS_CP    = copy
  OS_MKDIR = mkdir  
  export CC = gcc
else
  .DEFAULT_GOAL := gmake64
  OS_RM    = rm -f -r
  OS_RD    = rm -d -r
  OS_CP    = cp
  OS_MKDIR = mkdir -p  
endif

PROJECT = nmpp



#Generate GNU Makefiles :	https://github.com/premake/premake-core/wiki/Using-Premake
gmake32:
	$(OS_CP) Makefile .Makefile.origin
	premake5 gmake2
	$(OS_CP) Makefile .Makefile.premake
	$(OS_CP) .Makefile.origin Makefile
	$(OS_RM) .Makefile.origin 
	$(MAKE) -f .Makefile.premake nmpp config=release_x86


gmake64:
	$(OS_CP) Makefile .Makefile.origin
	premake5 gmake2
	$(OS_CP) Makefile .Makefile.premake
	$(OS_CP) .Makefile.origin Makefile
	$(OS_RM) .Makefile.origin 
	$(MAKE) -f .Makefile.premake nmpp config=release_x64

	
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
	"$(VS150COMNTOOLS)\VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=win32
	"$(VS150COMNTOOLS)\VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=win32
	"$(VS150COMNTOOLS)\VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Release /property:Platform=x64
	"$(VS150COMNTOOLS)\VsDevCmd" && msbuild nmpp.vcxproj /p:Configuration=Debug   /property:Platform=x64


	
cmake-mingw:
	-$(OS_RD)   MinGW	
	$(OS_MKDIR) MinGW
	cd    		MinGW && cmake .. -G "MinGW Makefiles"
#	cd    		MinGW && set path=$(MINGW)/bin;$(PATH) &&	cmake .. -G "MinGW Makefiles" 


cmake-unix:     
	-$(OS_RD)   Unix	
	$(OS_MKDIR)    Unix
	cd          Unix &&  cmake .. -G "Unix Makefiles" 
#	cd          Unix &&  set path=$(MINGW)/bin;$(PATH) && cmake .. -G "Unix Makefiles" -DCMAKE_POSITION_INDEPENDENT_CODE=ON
	
unix: Unix/Makefile
	$(MAKE) -C Unix
#	-DCMAKE_C_COMPILER="d:/SDK/MinGW/bin/gcc" -DCMAKE_CXX_COMPILER="d:/SDK/MinGW/bin/g++"  -DCMAKE_MAKE_PROGRAM="d:/SDK/MinGW/bin/mingw32-make" 


#include $(ROOT)/clean.mk
clean:
	-$(OS_RD) 1 2 3 4 obj 
	-$(OS_RM) .Makefile.* nmpp.make
	