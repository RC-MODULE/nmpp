#!lua

-- A solution contains projects, and defines the available configurations
  solution "test-x64"		 
	configurations { "Debug", "Release" }
	project "test-x64"
      kind "ConsoleApp"
      language "C++"
      files { "../*.cpp" }
	  links { "nmpp-x64"} 
	  libdirs { "$(NMPP)/lib","$(HAL)/lib"}
	  includedirs { "$(NMPP)/include","$(HAL)/include"}
	  systemversion 'latest'
      configuration "Debug"
         defines { "DEBUG" }
         symbols  "On" 
		 
		 

      configuration "Release"
         defines { "NDEBUG" }
         symbols  "Off" 
		 

