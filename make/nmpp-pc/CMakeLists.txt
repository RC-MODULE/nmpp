PROJECT(nmpp) 
# Like solution
MESSAGE(${CMAKE_CXX_FLAGS_DEBUG})
MESSAGE(${CMAKE_GENERATOR})
FILE(MAKE_DIRECTORY ${CMAKE_GENERATOR})
#SET(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_GENERATOR})
SET(CMAKE_BUILD_DIRECTORY d:/GIT/nmpp/make/nmpp-pc/lib)
#set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY  d:/GIT/nmpp/make/nmpp-pc/lib)

set(CMAKE_C_COMPILER d:/SDK/mingw32/bin)
set(CMAKE_CXX_COMPILER d:/SDK/mingw32/bin)

SET(ROOT ../..)
include_directories(
		${ROOT}/include 
		${ROOT}/include/nmplv 
		${ROOT}/include/nmpli 
		${ROOT}/include/nmpls 
		${ROOT}/include/nmplm 
		${ROOT}/include/nmplc )

FILE(GLOB  SRC 
		${ROOT}/src/nmplc/arithmetic/common *.cpp
		${ROOT}/src/nmplc/fixpoint32/pc/*.cpp
		${ROOT}/src/nmplc/fixpoint32/pc/*.c
		${ROOT}/src/nmplc/fixpoint64/pc/*.cpp
		${ROOT}/src/nmplc/init/common/*.cpp
		${ROOT}/src/nmplc/init/common/*.c
		${ROOT}/src/nmplc/integer/pc/*.cpp
		${ROOT}/src/nmpli/Arithmetics/pc/*.cpp
		${ROOT}/src/nmpli/Convert/common/*.cpp
		${ROOT}/src/nmpli/Convert/pc/*.cpp
		${ROOT}/src/nmpli/Filtration/common/*.cpp
		${ROOT}/src/nmpli/Filtration/common/*.c
		${ROOT}/src/nmpli/Filtration/pc/*.cpp
		${ROOT}/src/nmpli/Floodfill/common/*.cpp
		${ROOT}/src/nmpli/Floodfill/pc/*.cpp
		${ROOT}/src/nmpli/Init/common/*.cpp
		${ROOT}/src/nmpli/Print/pc/*.cpp
		${ROOT}/src/nmpli/Reodering/pc/*.cpp
		${ROOT}/src/nmpli/Resample/common/*.cpp
		${ROOT}/src/nmpli/Resample/pc/*.cpp
		${ROOT}/src/nmpli/Select/pc/*.cpp
		${ROOT}/src/nmpli/Select/common/*.cpp
		${ROOT}/src/nmpli/Support/common/*.cpp
		${ROOT}/src/nmplm/Core/pc/*.cpp
		${ROOT}/src/nmplm/Init/pc/*.cpp
		${ROOT}/src/nmplm/Inverse/common/*.cpp
		${ROOT}/src/nmplm/MatrixVector/pc/*.cpp
		${ROOT}/src/nmplm/MatrixVector/pc/*.c
		${ROOT}/src/nmplm/Support/common/*.cpp
		${ROOT}/src/nmpls/Correlation/pc/*.cpp
		${ROOT}/src/nmpls/FFT/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0032/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0032/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT0032/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0032/common/*.c
		${ROOT}/src/nmpls/FFT/FFT0064/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0064/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT0064/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0064/common/*.c
		${ROOT}/src/nmpls/FFT/FFT0256/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0256/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT0256/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0256/common/*.c
		${ROOT}/src/nmpls/FFT/FFT0512/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0512/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT0512/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT0512/common/*.c
		${ROOT}/src/nmpls/FFT/FFT1024/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT1024/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT1024/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT1024/common/*.c
		${ROOT}/src/nmpls/FFT/FFT2048/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT2048/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT2048/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT2048/common/*.c
		${ROOT}/src/nmpls/FFT/FFT4096/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT4096/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT8192/pc/*.cpp
		${ROOT}/src/nmpls/FFT/FFT8192/pc/*.c
		${ROOT}/src/nmpls/FFT/FFT8192/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFT8192/common/*.c
		${ROOT}/src/nmpls/FFT/IFFT0256/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT0256/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT0512/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT0512/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT1024/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT1024/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT2048/common/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT2048/common/*.c
		${ROOT}/src/nmpls/FFT/IFFT2048/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT2048/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT4096/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT4096/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT8192/pc/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT8192/pc/*.c
		${ROOT}/src/nmpls/FFT/IFFT8192/common/*.cpp
		${ROOT}/src/nmpls/FFT/IFFT8192/common/*.c
		${ROOT}/src/nmpls/FFT/FFTFree/common/*.cpp
		${ROOT}/src/nmpls/FFT/FFTFree/common/*.c
		${ROOT}/src/nmpls/Filter/common/*.cpp
		${ROOT}/src/nmpls/Filter/common/*.c
		${ROOT}/src/nmpls/Filtration/pc/*.cpp
		${ROOT}/src/nmpls/Filtration/pc/*.c
		${ROOT}/src/nmpls/Metric/*.cpp
		${ROOT}/src/nmpls/Metric/*.c
		${ROOT}/src/nmpls/Resample/common/*.cpp
		${ROOT}/src/nmpls/Resample/pc/*.cpp
		${ROOT}/src/nmplv/Arithmetics/common/*.cpp
		${ROOT}/src/nmplv/Arithmetics/common/*.c
		${ROOT}/src/nmplv/Arithmetics/pc/*.cpp
		${ROOT}/src/nmplv/Arithmetics/pc/*.c
		${ROOT}/src/nmplv/Bitwise/pc/*.cpp
		${ROOT}/src/nmplv/Bitwise/pc/*.c
		${ROOT}/src/nmplv/Init/common/*.cpp
		${ROOT}/src/nmplv/Init/common/*.c
		${ROOT}/src/nmplv/Init/pc/*.cpp
		${ROOT}/src/nmplv/Init/pc/*.c
		${ROOT}/src/nmplv/Select/common/*.cpp
		${ROOT}/src/nmplv/Select/common/*.c
		${ROOT}/src/nmplv/Select/pc/*.cpp
		${ROOT}/src/nmplv/Select/pc/*.c
		${ROOT}/src/nmplv/Stat/common/*.cpp
		${ROOT}/src/nmplv/Stat/common/*.c
		${ROOT}/src/nmplv/Stat/pc/*.cpp
		${ROOT}/src/nmplv/Stat/pc/*.c
		${ROOT}/src/nmplv/Support/pc/*.cpp
		${ROOT}/src/nmplv/Support/pc/*.c
		${ROOT}/src/nmplv/Support/common/*.cpp
		${ROOT}/src/nmplv/Support/common/*.c
		${ROOT}/src/nmplv/Tables/pc/*.cpp
		${ROOT}/src/nmplv/Tables/pc/*.c
		${ROOT}/src/nmplv/Transform/common/*.cpp
		${ROOT}/src/nmplv/Transform/common/*.c
		${ROOT}/src/nmplv/Transform/pc/*.cpp
		${ROOT}/src/nmplv/Transform/pc/*.c
)			

#FILE(GLOB_RECURSE RELATIVE files "../src/*.c")
#MESSAGE(STATUS ${files})
#FOREACH(item ${files})
#  IF(${item} MATCHES "[.]*rpc-arm[.]*")
#    LIST(REMOVE_ITEM files ${item})
#  ENDIF(${item} MATCHES [.]*rpc-arm[.]*)
#ENDFOREACH(item)
#MESSAGE(STATUS "${files}")


#file(GLOB ENDF6_SRC

       #${PROJECT_SOURCE_DIR}/*.cpp
       #${PROJECT_SOURCE_DIR}/File/*.cpp
       #${PROJECT_SOURCE_DIR}/Section/*.cpp)
#AUX_SOURCE_DIRECTORY(. SRC) 


#set(SRC main.c)

ADD_LIBRARY(nmpp ${SRC})