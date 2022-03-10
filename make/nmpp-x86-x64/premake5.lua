#!lua
-- https://premake.github.io/
ROOT = "../.."
-- A solution contains projects, and defines the available configurations
solution "nmpp"
	
    configurations { "Release", "Debug" }
	
	filter {"system:linux", "action:gmake*"}
		platforms { "x86","x64"}
  
	filter {"system:windows", "action:gmake*"}
		platforms { "x86","x64"}

	filter {"system:windows", "action:vs*"}
		platforms { "x86","x64"}
		systemversion ="latest"
		
      	
	project "nmpp"
	  --objdir ("o")
		kind "StaticLib"
		
		DIRS={}                                                 
		table.insert(DIRS,"/src/float/arithmetic"             )
		table.insert(DIRS,"/src/float/conditional"            )
		table.insert(DIRS,"/src/float/init"                   )
		table.insert(DIRS,"/src/float/linear"                 )
		table.insert(DIRS,"/src/float/metric"                 )
		table.insert(DIRS,"/src/float/nmblas/core"            )
		table.insert(DIRS,"/src/float/nmblas/level1"          )
		table.insert(DIRS,"/src/float/nmblas/level2"          )
		table.insert(DIRS,"/src/float/transform/fft"          )
		table.insert(DIRS,"/src/float/transform/fft/FFTFree"  )
		table.insert(DIRS,"/src/float/transform/fft/FFT0032"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT0032" )
		table.insert(DIRS,"/src/float/transform/fft/FFT0064"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT0064" )
		table.insert(DIRS,"/src/float/transform/fft/FFT0128"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT0128" )
		table.insert(DIRS,"/src/float/transform/fft/FFT0256"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT0256" )
		table.insert(DIRS,"/src/float/transform/fft/FFT0512"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT0512" )
		table.insert(DIRS,"/src/float/transform/fft/FFT1024"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT1024" )
		table.insert(DIRS,"/src/float/transform/fft/FFT2048"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT2048" )
		table.insert(DIRS,"/src/float/transform/fft/FFT4096"  )
		table.insert(DIRS,"/src/float/transform/fft/IFFT4096" )
		table.insert(DIRS,"/src/float/statistical/NormDiff"   )
		table.insert(DIRS,"/src/float/statistical/Norm"       )
		
		table.insert(DIRS,"/src/risc/fixpoint32")
		table.insert(DIRS,"/src/risc/fixpoint64")
		table.insert(DIRS,"/src/risc/init") 
		table.insert(DIRS,"/src/risc/linear") 
		table.insert(DIRS,"/src/risc/metric") 
		table.insert(DIRS,"/src/risc/support") 
		table.insert(DIRS,"/src/risc/tables") 
		
		SRC={}
		for _,i in pairs(DIRS) do
			table.insert(SRC,"ROOT..\""..i.."/pc/*.cpp\",") 
			table.insert(SRC,"ROOT..\""..i.."/pc/*.c\",") 
			table.insert(SRC,"ROOT..\""..i.."/common/*.cpp\",") 
			table.insert(SRC,"ROOT..\""..i.."/common/*.c\",") 
			-- print(i); -- 1 "a", 2 "b", 3 "c".
		end
		
		--for _,i in pairs(SRC) do
		--	print(i); -- 1 "a", 2 "b", 3 "c".
		--end


	  files { ROOT.."../include/*.h",
ROOT.."/src/float/arithmetic/pc/*.cpp",
ROOT.."/src/float/arithmetic/pc/*.c",
ROOT.."/src/float/arithmetic/common/*.cpp",
ROOT.."/src/float/arithmetic/common/*.c",
ROOT.."/src/float/conditional/pc/*.cpp",
ROOT.."/src/float/conditional/pc/*.c",
ROOT.."/src/float/conditional/common/*.cpp",
ROOT.."/src/float/conditional/common/*.c",
ROOT.."/src/float/init/pc/*.cpp",
ROOT.."/src/float/init/pc/*.c",
ROOT.."/src/float/init/common/*.cpp",
ROOT.."/src/float/init/common/*.c",
ROOT.."/src/float/linear/pc/*.cpp",
ROOT.."/src/float/linear/pc/*.c",
ROOT.."/src/float/linear/common/*.cpp",
ROOT.."/src/float/linear/common/*.c",
ROOT.."/src/float/metric/pc/*.cpp",
ROOT.."/src/float/metric/pc/*.c",
ROOT.."/src/float/metric/common/*.cpp",
ROOT.."/src/float/metric/common/*.c",
ROOT.."/src/float/nmblas/core/pc/*.cpp",
ROOT.."/src/float/nmblas/core/pc/*.c",
ROOT.."/src/float/nmblas/core/common/*.cpp",
ROOT.."/src/float/nmblas/core/common/*.c",
ROOT.."/src/float/nmblas/level1/pc/*.cpp",
ROOT.."/src/float/nmblas/level1/pc/*.c",
ROOT.."/src/float/nmblas/level1/common/*.cpp",
ROOT.."/src/float/nmblas/level1/common/*.c",
ROOT.."/src/float/nmblas/level2/pc/*.cpp",
ROOT.."/src/float/nmblas/level2/pc/*.c",
ROOT.."/src/float/nmblas/level2/common/*.cpp",
ROOT.."/src/float/nmblas/level2/common/*.c",
ROOT.."/src/float/transform/fft/pc/*.cpp",
ROOT.."/src/float/transform/fft/pc/*.c",
ROOT.."/src/float/transform/fft/common/*.cpp",
ROOT.."/src/float/transform/fft/common/*.c",
ROOT.."/src/float/transform/fft/FFTFree/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFTFree/pc/*.c",
ROOT.."/src/float/transform/fft/FFTFree/common/*.cpp",
ROOT.."/src/float/transform/fft/FFTFree/common/*.c",
ROOT.."/src/float/transform/fft/DFT0008/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0016/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0032/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0032/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT0032/common/*.c",
ROOT.."/src/float/transform/fft/IFFT0032/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0032/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT0032/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0032/common/*.c",
ROOT.."/src/float/transform/fft/FFT0064/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT0064/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0064/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT0064/common/*.c",
ROOT.."/src/float/transform/fft/IFFT0064/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0064/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT0064/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0064/common/*.c",
ROOT.."/src/float/transform/fft/FFT0128/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT0128/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0128/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT0128/common/*.c",
ROOT.."/src/float/transform/fft/IFFT0128/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0128/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT0128/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0128/common/*.c",
ROOT.."/src/float/transform/fft/FFT0256/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT0256/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0256/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT0256/common/*.c",
ROOT.."/src/float/transform/fft/IFFT0256/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0256/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT0256/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0256/common/*.c",
ROOT.."/src/float/transform/fft/FFT0512/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT0512/pc/*.c",
ROOT.."/src/float/transform/fft/FFT0512/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT0512/common/*.c",
ROOT.."/src/float/transform/fft/IFFT0512/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0512/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT0512/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT0512/common/*.c",
ROOT.."/src/float/transform/fft/FFT1024/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT1024/pc/*.c",
ROOT.."/src/float/transform/fft/FFT1024/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT1024/common/*.c",
ROOT.."/src/float/transform/fft/IFFT1024/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT1024/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT1024/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT1024/common/*.c",
ROOT.."/src/float/transform/fft/FFT2048/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT2048/pc/*.c",
ROOT.."/src/float/transform/fft/FFT2048/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT2048/common/*.c",
ROOT.."/src/float/transform/fft/IFFT2048/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT2048/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT2048/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT2048/common/*.c",
ROOT.."/src/float/transform/fft/FFT4096/pc/*.cpp",
ROOT.."/src/float/transform/fft/FFT4096/pc/*.c",
ROOT.."/src/float/transform/fft/FFT4096/common/*.cpp",
ROOT.."/src/float/transform/fft/FFT4096/common/*.c",
ROOT.."/src/float/transform/fft/IFFT4096/pc/*.cpp",
ROOT.."/src/float/transform/fft/IFFT4096/pc/*.c",
ROOT.."/src/float/transform/fft/IFFT4096/common/*.cpp",
ROOT.."/src/float/transform/fft/IFFT4096/common/*.c",
ROOT.."/src/float/statistical/NormDiff/pc/*.cpp",
ROOT.."/src/float/statistical/NormDiff/pc/*.c",
ROOT.."/src/float/statistical/NormDiff/common/*.cpp",
ROOT.."/src/float/statistical/NormDiff/common/*.c",
ROOT.."/src/float/statistical/Norm/pc/*.cpp",
ROOT.."/src/float/statistical/Norm/pc/*.c",
ROOT.."/src/float/statistical/Norm/common/*.cpp",
ROOT.."/src/float/statistical/Norm/common/*.c",
ROOT.."/src/risc/fixpoint32/pc/*.cpp",
ROOT.."/src/risc/fixpoint32/pc/*.c",
ROOT.."/src/risc/fixpoint32/common/*.cpp",
ROOT.."/src/risc/fixpoint32/common/*.c",
ROOT.."/src/risc/fixpoint64/pc/*.cpp",
ROOT.."/src/risc/fixpoint64/pc/*.c",
ROOT.."/src/risc/fixpoint64/common/*.cpp",
ROOT.."/src/risc/fixpoint64/common/*.c",
ROOT.."/src/risc/init/pc/*.cpp",
ROOT.."/src/risc/init/pc/*.c",
ROOT.."/src/risc/init/common/*.cpp",
ROOT.."/src/risc/init/common/*.c",
ROOT.."/src/risc/linear/pc/*.cpp",
ROOT.."/src/risc/linear/pc/*.c",
ROOT.."/src/risc/linear/common/*.cpp",
ROOT.."/src/risc/linear/common/*.c",
ROOT.."/src/risc/metric/pc/*.cpp",
ROOT.."/src/risc/metric/pc/*.c",
ROOT.."/src/risc/metric/common/*.cpp",
ROOT.."/src/risc/metric/common/*.c",
ROOT.."/src/risc/support/pc/*.cpp",
ROOT.."/src/risc/support/pc/*.c",
ROOT.."/src/risc/support/common/*.cpp",
ROOT.."/src/risc/support/common/*.c",
ROOT.."/src/risc/tables/pc/*.cpp",
ROOT.."/src/risc/tables/pc/*.c",
ROOT.."/src/risc/tables/common/*.cpp",
ROOT.."/src/risc/tables/common/*.c"



		--SRC
		--ROOT.."/src/nmblas/level1/pc/*.c",
		--ROOT.."/src/nmblas/level2/pc/*.c",
	  	--ROOT.."/src/nmplc/arithmetic/common/*.cpp",
		--ROOT.."/src/nmplc/fixpoint32/pc/*.cpp",
		--ROOT.."/src/nmplc/fixpoint32/pc/*.c",
		--ROOT.."/src/nmplc/fixpoint64/pc/*.cpp",
		--ROOT.."/src/nmplc/init/common/*.cpp",
		--ROOT.."/src/nmplc/init/common/*.c",
		--ROOT.."/src/nmplc/integer/pc/*.c",
		--ROOT.."/src/nmplc/integer/pc/*.cpp",
		--ROOT.."/src/nmpli/Arithmetics/pc/*.cpp",
		--ROOT.."/src/nmpli/Convert/common/*.cpp",
		--ROOT.."/src/nmpli/Convert/pc/*.cpp",
		--ROOT.."/src/nmpli/Filtration/common/*.cpp",
		--ROOT.."/src/nmpli/Filtration/common/*.c",
		--ROOT.."/src/nmpli/Filtration/pc/*.cpp",
		--ROOT.."/src/nmpli/Floodfill/common/*.cpp",
		--ROOT.."/src/nmpli/Floodfill/pc/*.cpp",
		--ROOT.."/src/nmpli/Init/common/*.cpp",
		--ROOT.."/src/nmpli/Print/pc/*.cpp",
		--ROOT.."/src/nmpli/Reodering/pc/*.cpp",
		--ROOT.."/src/nmpli/Resample/common/*.cpp",
		--ROOT.."/src/nmpli/Resample/pc/*.cpp",
		--ROOT.."/src/nmpli/Select/pc/*.cpp",
		--ROOT.."/src/nmpli/Select/common/*.cpp",
		--ROOT.."/src/nmpli/Support/common/*.cpp",
		--ROOT.."/src/nmplm/Core/pc/*.cpp",
		--ROOT.."/src/nmplm/Init/pc/*.cpp",
		--ROOT.."/src/nmplm/Init/pc/*.c	",
		--ROOT.."/src/nmplm/Inverse/common/*.cpp",
		--ROOT.."/src/nmplm/MatrixVector/pc/*.cpp",
		--ROOT.."/src/nmplm/MatrixVector/pc/*.c",
		--ROOT.."/src/nmplm/Support/common/*.cpp",
		--ROOT.."/src/nmpls/Correlation/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0016/common/*.*",
		--ROOT.."/src/nmpls/FFT/FFT0016/pc/*.*",
		--ROOT.."/src/nmpls/FFT/FFT0032/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0032/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0032/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0032/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0064/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0064/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0064/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0064/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0256/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0256/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0256/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0256/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0512/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0512/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT0512/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT0512/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT1024/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT1024/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT1024/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT1024/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT2048/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT2048/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT2048/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT2048/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFT4096/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT4096/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT8192/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT8192/pc/*.c",
		--ROOT.."/src/nmpls/FFT/FFT8192/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFT8192/common/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT0256/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT0256/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT0512/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT0512/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT1024/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT1024/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT2048/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT2048/common/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT2048/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT2048/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT4096/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT4096/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT8192/pc/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT8192/pc/*.c",
		--ROOT.."/src/nmpls/FFT/IFFT8192/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/IFFT8192/common/*.c",
		--ROOT.."/src/nmpls/FFT/FFTFree/common/*.cpp",
		--ROOT.."/src/nmpls/FFT/FFTFree/common/*.c",
		--ROOT.."/src/nmpls/Filter/common/*.cpp",
		--ROOT.."/src/nmpls/Filter/common/*.c",
		--ROOT.."/src/nmpls/Filtration/pc/*.cpp",
		--ROOT.."/src/nmpls/Filtration/pc/*.c",
		--ROOT.."/src/nmpls/Filtration/common/*.cpp",
		--ROOT.."/src/nmpls/Filtration/common/*.c",
		--ROOT.."/src/nmpls/Metric/*.cpp",
		--ROOT.."/src/nmpls/Metric/*.c",
		--ROOT.."/src/nmpls/Resample/common/*.cpp",
		--ROOT.."/src/nmpls/Resample/pc/*.cpp",
		--ROOT.."/src/nmpls/Arithmetics/pc/*.c",
		--ROOT.."/src/nmplv/Arithmetics/common/*.cpp",
		--ROOT.."/src/nmplv/Arithmetics/common/*.c",
		--ROOT.."/src/nmplv/Arithmetics/pc/*.cpp",
		--ROOT.."/src/nmplv/Arithmetics/pc/*.c",
		--ROOT.."/src/nmplv/Bitwise/pc/*.cpp",
		--ROOT.."/src/nmplv/Bitwise/pc/*.c",
		--ROOT.."/src/nmplv/Init/common/*.cpp",
		--ROOT.."/src/nmplv/Init/common/*.c",
		--ROOT.."/src/nmplv/Init/pc/*.cpp",
		--ROOT.."/src/nmplv/Init/pc/*.c",
		--ROOT.."/src/nmplv/Select/common/*.cpp",
		--ROOT.."/src/nmplv/Select/common/*.c",
		--ROOT.."/src/nmplv/Select/pc/*.cpp",
		--ROOT.."/src/nmplv/Select/pc/*.c",
		--ROOT.."/src/nmplv/Stat/common/*.cpp",
		--ROOT.."/src/nmplv/Stat/common/*.c",
		--ROOT.."/src/nmplv/Stat/pc/*.cpp",
		--ROOT.."/src/nmplv/Stat/pc/*.c",
		--ROOT.."/src/nmplv/Support/pc/*.cpp",
		--ROOT.."/src/nmplv/Support/pc/*.c",
		--ROOT.."/src/nmplv/Support/common/*.cpp",
		--ROOT.."/src/nmplv/Support/common/*.c",
		--ROOT.."/src/nmplv/Tables/pc/*.cpp",
		--ROOT.."/src/nmplv/Tables/pc/*.c",
		--ROOT.."/src/nmplv/Transform/common/*.cpp",
		--ROOT.."/src/nmplv/Transform/common/*.c",
		--ROOT.."/src/nmplv/Transform/pc/*.cpp",
		--ROOT.."/src/nmplv/Transform/pc/*.c",
		--ROOT.."/src/nmplv/Init/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/DFT0008/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0016/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0032/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0064/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0128/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0256/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT0512/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT1024/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT2048/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFT4096/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IDFT0008/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0016/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0032/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0064/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0128/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0256/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT0512/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT1024/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT2048/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/IFFT4096/pc/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/common/*.c",
		--ROOT.."/src/nmpls/FFT_32fcr/FFTFree/common/*.c",
		--ROOT.."/src/nmpls/FFT0032/pc/*.c",
		--ROOT.."/src/nmpls/FFT0064/pc/*.c",
		--ROOT.."/src/nmpls/FFT0128/pc/*.c",
		--ROOT.."/src/nmpls/FFT0256/pc/*.c",
		--ROOT.."/src/nmpls/FFT0512/pc/*.c",
		--ROOT.."/src/nmpls/FFT1024/pc/*.c",
		--ROOT.."/src/nmpls/FFT2048/pc/*.c"
		}
		
		
		
		includedirs { ROOT.."/include",ROOT.."/include/nmpls","$(HAL)/include"}
		  
		targetdir (ROOT.."/lib")
		
		
		configuration {"Debug","x86"}
			cppdialect "C++11"
			targetsuffix ("-x86d")
			architecture "x86"
			defines { "DEBUG"}
			symbols  ="On" 
			objdir "1"
		
		configuration {"Release","x86"}
			cppdialect "C++11"
			targetsuffix ("-x86")
			architecture "x86"
			defines { "NDEBUG"}
			symbols  ="Off" 
			objdir "2"
		
		configuration {"Debug","x64"}
			cppdialect "C++11"
			targetsuffix ("-x64d")
			architecture "x86_64"
			defines { "DEBUG"}
			symbols  ="On" 
			objdir "3"
		
		configuration {"Release","x64"}
			cppdialect "C++11"
			targetsuffix ("-x64")
			architecture "x86_64"
			defines { "NDEBUG"}
			symbols  ="Off" 
			objdir "4"
	 
 
