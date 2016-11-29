cmake_minimum_required(VERSION 3.5)
PROJECT(nmpp) 
MESSAGE(STATUS ${CMAKE_GENERATOR})



MESSAGE(STATUS ${CMAKE_SIZEOF_VOID_P})
IF(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	SET(CMAKE_DEBUG_POSTFIX   "-x86d")
	SET(CMAKE_RELEASE_POSTFIX "-x86")
ELSE (${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	SET(CMAKE_DEBUG_POSTFIX   "-x64d")
	SET(CMAKE_RELEASE_POSTFIX "-x64")
ENDIF (${CMAKE_SIZEOF_VOID_P} EQUAL 4)

SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${ROOT}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${ROOT}/lib)



SET(CompilerFlags
       CMAKE_CXX_FLAGS
       CMAKE_CXX_FLAGS_DEBUG
       CMAKE_CXX_FLAGS_RELEASE
       CMAKE_C_FLAGS
       CMAKE_C_FLAGS_DEBUG
       CMAKE_C_FLAGS_RELEASE
       )
foreach(CompilerFlag ${CompilerFlags})
 string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()


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

ADD_LIBRARY(nmpp ${SRC} )

#MESSAGE(STATUS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
#if ( MSVC )
#   set_target_properties( nmpp-x86 PROPERTIES LIBRARY_OUTPUT_DIRECTORY 		d:/GIT/nmpp/1111)
#   set_target_properties( nmpp-x86 PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG 	d:/GIT/nmpp/1111)
#   set_target_properties( nmpp-x86 PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE d:/GIT/nmpp/1111)
#	set_target_properties( nmpp-x86 PROPERTIES RUNTIME_OUTPUT_DIRECTORY 		d:/GIT/nmpp/1111)
#   set_target_properties( nmpp-x86 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG 	d:/GIT/nmpp/1111)
#   set_target_properties( nmpp-x86 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE d:/GIT/nmpp/1111)
#set_target_properties( nmpp PROPERTIES ARCHIVE_DIRECTORY 		 d:/GIT/nmpp/1111)
#set_target_properties( nmpp PROPERTIES ARCHIVE_DIRECTORY_DEBUG 	 d:/GIT/nmpp/1111)
#set_target_properties( nmpp PROPERTIES ARCHIVE_DIRECTORY_RELEASE d:/GIT/nmpp/1111)
#set_target_properties( nmpp PROPERTIES OUTPUT_NAME_DEBUG 123 )		# name of debug lib + prefix
#set_target_properties( nmpp PROPERTIES OUTPUT_NAME_RELEASE 123 )	# name of release lib

  

#MESSAGE(STATUS ${ARCHIVE_OUTPUT_DIRECTORY})
#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${ROOT}/lib)
#MESSAGE(STATUS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
#MESSAGE(STATUS ${LIBRARY_OUTPUT_DIRECTORY}) - Debug/release dir
#SET(CMAKE_BUILD_DIRECTORY ${ROOT}/lib)
#SET(LIBRARY_OUTPUT_PATH   ${ROOT}/lib )  # Create ${ROOT}/lib/debug
#SET(LIBRARY_OUTPUT_NAME 1111) - # FAILED
#SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${ROOT}/lib)
#set(CMAKE_C_COMPILER d:/SDK/mingw32/bin)
#set(CMAKE_CXX_COMPILER d:/SDK/mingw32/bin)
#MESSAGE(${CMAKE_OSX_ARCHITECTURES})
#FILE(MAKE_DIRECTORY ${CMAKE_GENERATOR})
#SET(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_GENERATOR})
#MESSAGE(STATUS ${CMAKE_CXX_FLAGS_DEBUG})
#MESSAGE(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#MESSAGE(STATUS ${CMAKE_SYSTEM_PROCESSOR})


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
#SET(LIBRARY_OUTPUT_DIRECTORY 			d:/GIT/nmpp/lib)
#SET(LIBRARY_OUTPUT_DIRECTORY_DEBUG 		d:/GIT/nmpp/lib)
#SET(LIBRARY_OUTPUT_DIRECTORY_RELEASE 	d:/GIT/nmpp/lib)
#MESSAGE(STATUS "##############" ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY d:/GIT/nmpp/1111)
