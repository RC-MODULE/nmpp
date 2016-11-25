VS8     = "Visual_Studio_8_2005"
VS12    = "Visual_Studio_12_2013"
VS12X64 = "Visual_Studio_12_2013_Win64"
VS14    = "Visual_Studio_14_2014"
VS14X64 = "Visual_Studio_14_2014_Win64"

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


all: configure-vs8  vs8 configure-vs12 vs12 configure-vs12x64 vs12x64

configure-vs8: 
	-$(RMDIR)	$(VS8)
	$(MKDIR) 	$(VS8)
	cd    		$(VS8) &&	cmake .. -G "Visual Studio 8 2005"
            
vs8:        
	cd    		$(VS8) && "$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.vcproj
	
#	$(CP)		$(call OSX,$(VS8)/Debug/*.lib) 	$(call OSX,../../lib/)
#	$(CP)  		$(call OSX,$(VS8)/Release/*.lib) $(call OSX,../../lib/)

	
configure-vs12 :
	-$(RMDIR)	$(VS12)
	$(MKDIR)	$(VS12)
	cd    		$(VS12) &&	cmake .. -G "Visual Studio 12 2013"

	
vs12: 
	cd    		$(VS12) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    		$(VS12) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release

#	$(CP)   	$(call OSX,$(VS12)/Debug/*.lib)     $(call OSX,../../lib/)
#	$(CP)   	$(call OSX,$(VS12)/Release/*.lib) 	$(call OSX,../../lib/)

	

configure-vs12x64 :
	-$(RMDIR) 	$(VS12X64)
	$(MKDIR) 	$(VS12X64)
	cd    		$(VS12X64) &&	cmake .. -G  "Visual Studio 12 2013 Win64"

vs12x64:  
	cd    		$(VS12X64) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    		$(VS12X64) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release

#	$(CP) 		$(call OSX,$(VS12X64)/Debug/nmpp.lib)   $(call OSX,../../lib/nmpp-x64d.lib)
#	$(CP) 		$(call OSX,$(VS12X64)/Release/nmpp.lib) $(call OSX,../../lib/nmpp-x64.lib)


configure-vs14 :
	-$(RMDIR)   $(VS14)
	$(MKDIR) 	$(VS14)
	cd    		$(VS14) &&	cmake .. -G  "Visual Studio 14 2015 Win64"

vs14:  
	cd    		$(VS14) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    		$(VS14) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release

#	cp    		$(call OSX,$(VS14)/Debug/nmpp.lib) 	$(call OSX ../../lib/nmpp-x86d.lib)
#	cp    		$(call OSX,$(VS14)/Release/nmpp.lib)$(call OSX,../../lib/nmpp-x86.lib)

	
configure-vs14x64 :
	-$(RMDIR)   $(VS14X64)
	$(MKDIR) 	$(VS14X64)
	cd   		$(VS14X64) &&	cmake .. -G  "Visual Studio 14 2015 Win64"

vs14x64:  
	cd    		$(VS14X64) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    		$(VS14X64) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release

#	$(CP)  		$(call OSX,$(VS14X64)/Debug/nmpp.lib)   $(call OSX,../../lib/nmpp-x64d.lib)
#	$(CP)  		$(call OSX,$(VS14X64)/Release/nmpp.lib) $(call OSX,../../lib/nmpp-x64.lib)
	
msys:	
	$(MKDIR) 	"MSYS"
	cd    		"MSYS" &&	cmake .. -G "MSYS Makefiles"

mingw:	
	$(MKDIR) 	"MinGW"
	cd    		"MinGW" &&	cmake .. -G "MinGW Makefiles"

clean:
	$(RMDIR) $(VS8) $(VS12)  $(VS12X64) $(VS14) $(VS14X64)
	