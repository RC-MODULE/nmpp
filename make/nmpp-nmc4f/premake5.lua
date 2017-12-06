#!lua

-- A solution contains projects, and defines the available configurations
solution "nmpp"
   configurations { "Debug", "Release" }

	project "nmpp-nmc4f"
      kind "Makefile"
	  
      files { "../include/*.h", "Makefile" }
	 
	  configuration "Debug"
		   buildcommands {"make DEBUG=y -f Makefile"}
		   rebuildcommands {"make -B DEBUG=y -f Makefile"}
		   cleancommands {"make clean"}
		   
	  configuration "Release"
		   buildcommands {"make -f Makefile"}
		   rebuildcommands {"make -B -f Makefile"}
		   cleancommands {"make clean"}		   
		
		
		