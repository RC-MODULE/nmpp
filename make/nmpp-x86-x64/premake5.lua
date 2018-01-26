#!lua
ROOT = "../.."
-- A solution contains projects, and defines the available configurations
solution "nmpp"
   configurations { "Debug", "Release" }

	project "nmpp-nmc4"
      kind "Makefile"
      files { "../src/*.*",ROOT.."../include/*.h", "Makefile" }
	 
	  configuration "Debug"
		   buildcommands {"make DEBUG=y -f Makefile"}
		   rebuildcommands {"make -B DEBUG=y -f Makefile"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile"}
		   rebuildcommands {"make -B -f Makefile"}
		   cleancommands {"make clean"}		   
		
		
		
	project "nmpp-x86"
      kind "StaticLib"
      files { ROOT.."../include/*.h",
	  	ROOT.."/src/nmplc/arithmetic/common/*.cpp",
		ROOT.."/src/nmplc/fixpoint32/pc/*.cpp",
		ROOT.."/src/nmplc/fixpoint32/pc/*.c",
		ROOT.."/src/nmplc/fixpoint64/pc/*.cpp",
		ROOT.."/src/nmplc/init/common/*.cpp",
		ROOT.."/src/nmplc/init/common/*.c",
		ROOT.."/src/nmplc/integer/pc/*.c",
		ROOT.."/src/nmplc/integer/pc/*.cpp",
		ROOT.."/src/nmpli/Arithmetics/pc/*.cpp",
		ROOT.."/src/nmpli/Convert/common/*.cpp",
		ROOT.."/src/nmpli/Convert/pc/*.cpp",
		ROOT.."/src/nmpli/Filtration/common/*.cpp",
		ROOT.."/src/nmpli/Filtration/common/*.c",
		ROOT.."/src/nmpli/Filtration/pc/*.cpp",
		ROOT.."/src/nmpli/Floodfill/common/*.cpp",
		ROOT.."/src/nmpli/Floodfill/pc/*.cpp",
		ROOT.."/src/nmpli/Init/common/*.cpp",
		ROOT.."/src/nmpli/Print/pc/*.cpp",
		ROOT.."/src/nmpli/Reodering/pc/*.cpp",
		ROOT.."/src/nmpli/Resample/common/*.cpp",
		ROOT.."/src/nmpli/Resample/pc/*.cpp",
		ROOT.."/src/nmpli/Select/pc/*.cpp",
		ROOT.."/src/nmpli/Select/common/*.cpp",
		ROOT.."/src/nmpli/Support/common/*.cpp",
		ROOT.."/src/nmplm/Core/pc/*.cpp",
		ROOT.."/src/nmplm/Init/pc/*.cpp",
		ROOT.."/src/nmplm/Inverse/common/*.cpp",
		ROOT.."/src/nmplm/MatrixVector/pc/*.cpp",
		ROOT.."/src/nmplm/MatrixVector/pc/*.c",
		ROOT.."/src/nmplm/Support/common/*.cpp",
		ROOT.."/src/nmpls/Correlation/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0032/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0032/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT0032/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0032/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT0064/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0064/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT0064/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0064/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT0256/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0256/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT0256/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0256/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT0512/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0512/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT0512/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT0512/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT1024/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT1024/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT1024/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT1024/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT2048/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT2048/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT2048/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT2048/common/*.c",
		ROOT.."/src/nmpls/FFT/FFT4096/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT4096/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT8192/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT8192/pc/*.c",
		ROOT.."/src/nmpls/FFT/FFT8192/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFT8192/common/*.c",
		ROOT.."/src/nmpls/FFT/IFFT0256/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT0256/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT0512/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT0512/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT1024/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT1024/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT2048/common/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT2048/common/*.c",
		ROOT.."/src/nmpls/FFT/IFFT2048/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT2048/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT4096/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT4096/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT8192/pc/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT8192/pc/*.c",
		ROOT.."/src/nmpls/FFT/IFFT8192/common/*.cpp",
		ROOT.."/src/nmpls/FFT/IFFT8192/common/*.c",
		ROOT.."/src/nmpls/FFT/FFTFree/common/*.cpp",
		ROOT.."/src/nmpls/FFT/FFTFree/common/*.c",
		ROOT.."/src/nmpls/Filter/common/*.cpp",
		ROOT.."/src/nmpls/Filter/common/*.c",
		ROOT.."/src/nmpls/Filtration/pc/*.cpp",
		ROOT.."/src/nmpls/Filtration/pc/*.c",
		ROOT.."/src/nmpls/Metric/*.cpp",
		ROOT.."/src/nmpls/Metric/*.c",
		ROOT.."/src/nmpls/Resample/common/*.cpp",
		ROOT.."/src/nmpls/Resample/pc/*.cpp",
		ROOT.."/src/nmplv/Arithmetics/common/*.cpp",
		ROOT.."/src/nmplv/Arithmetics/common/*.c",
		ROOT.."/src/nmplv/Arithmetics/pc/*.cpp",
		ROOT.."/src/nmplv/Arithmetics/pc/*.c",
		ROOT.."/src/nmplv/Bitwise/pc/*.cpp",
		ROOT.."/src/nmplv/Bitwise/pc/*.c",
		ROOT.."/src/nmplv/Init/common/*.cpp",
		ROOT.."/src/nmplv/Init/common/*.c",
		ROOT.."/src/nmplv/Init/pc/*.cpp",
		ROOT.."/src/nmplv/Init/pc/*.c",
		ROOT.."/src/nmplv/Select/common/*.cpp",
		ROOT.."/src/nmplv/Select/common/*.c",
		ROOT.."/src/nmplv/Select/pc/*.cpp",
		ROOT.."/src/nmplv/Select/pc/*.c",
		ROOT.."/src/nmplv/Stat/common/*.cpp",
		ROOT.."/src/nmplv/Stat/common/*.c",
		ROOT.."/src/nmplv/Stat/pc/*.cpp",
		ROOT.."/src/nmplv/Stat/pc/*.c",
		ROOT.."/src/nmplv/Support/pc/*.cpp",
		ROOT.."/src/nmplv/Support/pc/*.c",
		ROOT.."/src/nmplv/Support/common/*.cpp",
		ROOT.."/src/nmplv/Support/common/*.c",
		ROOT.."/src/nmplv/Tables/pc/*.cpp",
		ROOT.."/src/nmplv/Tables/pc/*.c",
		ROOT.."/src/nmplv/Transform/common/*.cpp",
		ROOT.."/src/nmplv/Transform/common/*.c",
		ROOT.."/src/nmplv/Transform/pc/*.cpp",
		ROOT.."/src/nmplv/Transform/pc/*.c",
		ROOT.."/src/nmplv/Init/pc_risc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/norm/common/*.c",
		ROOT.."/src/nmpls/FFT_32fc/DFT0008/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0016/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0032/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0064/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0128/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0256/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT0512/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT1024/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFT2048/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IDFT0008/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0016/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0032/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0064/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0128/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0256/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT0512/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT1024/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/IFFT2048/pc/*.c",
		ROOT.."/src/nmpls/FFT_32fc/common/*.c",
		ROOT.."/src/nmplv/Arithmetics/pc_f/*.c",
		ROOT.."/src/nmplv/Init/pc_f/*.c",
		ROOT.."/src/nmpls/FFT_32fc/FFTFree/common/*.c",
		ROOT.."/src/nmpls/FFT0032/pc/*.c",
		ROOT.."/src/nmpls/FFT0064/pc/*.c",
		ROOT.."/src/nmpls/FFT0128/pc/*.c",
		ROOT.."/src/nmpls/FFT0256/pc/*.c",
		ROOT.."/src/nmpls/FFT0512/pc/*.c",
		ROOT.."/src/nmpls/FFT1024/pc/*.c",
		ROOT.."/src/nmpls/FFT2048/pc/*.c"
	}
		
	includedirs { ROOT.."/include",ROOT.."/include/nmpls"}
	  
	  
	configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 targetdir (ROOT.."/lib")
		 

    configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 targetdir (ROOT.."/lib")
		
	 
 
