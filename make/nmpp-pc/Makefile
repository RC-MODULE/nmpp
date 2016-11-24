SHELL   = cmd
VS8     = "Visual_Studio_8_2005"
VS12    = "Visual_Studio_12_2013"
VS12X64 = "Visual_Studio_12_2013 Win64"
VS14    = "Visual_Studio_14_2014"
VS14X64 = "Visual_Studio_14_2014 Win64"

configure-vs8: 
	mkdir $(VS8)
	cd    $(VS8) &&	cmake .. -G "Visual Studio 8 2005"
            
vs8:        
	cd    $(VS8) && "$(VS80COMNTOOLS)vsvars32" && vcbuild nmpp.vcproj
	cp    $(VS8)/Debug/nmpp.lib ../../lib/nmpp-vs80d.lib
	cp    $(VS8)/Release/nmpp.lib ../../lib/nmpp-vs80.lib
	
#vs8x64:
#	mkdir "Visual Studio 8 2005 Win64"
#	cd    "Visual Studio 8 2005 Win64" && "$(VS80COMNTOOLS)vsvars32" &&	cmake .. -G "Visual Studio 8 2005 Win64"

#$(VS12)
configure-vs12 :
	rm    $(VS12) -f -r
	mkdir $(VS12)
	cd    $(VS12) &&	cmake .. -G "Visual Studio 12 2013"
	
vs12: 
	cd    $(VS12) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    $(VS12) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release
	cp    $(VS12)/Debug/nmpp.lib ../../lib/nmpp-vs12d.lib
	cp    $(VS12)/Release/nmpp.lib ../../lib/nmpp-vs12.lib
	

configure-vs12x64 :
	rm    $(VS12X64) -f -r
	mkdir $(VS12X64)
	cd    $(VS12X64) &&	cmake .. -G  "Visual Studio 12 2013 Win64"

vs12x64:  
	cd    $(VS12X64) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    $(VS12X64) && "$(VS120COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release
	cp    $(VS12X64)/Debug/nmpp.lib ../../lib/nmpp-vs12x64d.lib
	cp    $(VS12X64)/Release/nmpp.lib ../../lib/nmpp-vs12x64.lib


configure-vs14 :
	rm    $(VS14) -f -r
	mkdir $(VS14)
	cd    $(VS14) &&	cmake .. -G  "Visual Studio 14 2015 Win64"

vs14:  
	cd    $(VS14) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    $(VS14) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release
	cp    $(VS14)/Debug/nmpp.lib ../../lib/nmpp-vs14x64d.lib
	cp    $(VS14)/Release/nmpp.lib ../../lib/nmpp-vs14x64.lib

	
configure-vs14x64 :
	rm    $(VS14X64) -f -r
	mkdir $(VS14X64)
	cd    $(VS14X64) &&	cmake .. -G  "Visual Studio 14 2015 Win64"

vs14x64:  
	cd    $(VS14X64) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj
	cd    $(VS14X64) && "$(VS140COMNTOOLS)vsvars32" && msbuild nmpp.vcxproj /p:Configuration=Release
	cp    $(VS14X64)/Debug/nmpp.lib ../../lib/nmpp-vs14x64d.lib
	cp    $(VS14X64)/Release/nmpp.lib ../../lib/nmpp-vs14x64.lib
	

msys:	
	mkdir "MSYS"
	cd    "MSYS" &&	cmake .. -G "MSYS Makefiles"

mingw:	
	mkdir "MinGW"
	cd    "MinGW" &&	cmake .. -G "MinGW Makefiles"

clean:
	rm -f -r $(VS8) $(VS12)  $(VS12X64) $(VS14) $(VS14X64)
	