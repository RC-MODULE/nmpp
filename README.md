###DOCUMENTATION:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM: http://rc-module.github.io/nmpp/nmpp.chm  
  PDF: http://rc-module.github.io/nmpp/nmpp.pdf  

###DESCRIPTION:  
  NMPP is "Neuro Matrix Performance Primitives" library 
  which consists of scalar, vector-matrix  , signal and 
  image processing functions for Neuro Matrix architecture. 

###COMPONENTS:  
  NMPP library contains next components:  
  -nmvcore- basic low-level vector-cooprocessor functions  
  -nmplc  - scalar functions  
  -nmplv  - vector functions  
  -nmplm  - matrix functions  
  -nmpls  - signal processing functions  
  -nmpli  - image  processing functions  

  
###ARCHITECTURE:  
nmpp-library supports nmc3-core processor family : NM6405,NM6406, and SOCs  
  /lib/nmpp_nmc3.lib   (Release)  
  /lib/nmpp_nmc3d.lib  (Debug)  
supported boards:    
  MC5101 board  
  MC5103 board  
  M77601 board  
  MB7707 board  
 
It also have emulation libraries for x86:  
  /lib/libnmpp_gcc.a  - compiled by GNU GCC under Windows  
  /lib/nmpp_vs80.lib  - (Release) compiled by Microsoft Visual Studio 8.0  
  /lib/nmpp_vs80d.lib - (Debug)  
  /lib/nmpp_vs13.lib  - (Release) compiled by Microsoft Visual Studio 13.0  
  /lib/nmpp_vs13d.lib - (Debug)  

###BUILDING LIBRARY:  
  Run command 'make' to build all (nmc3, gcc , vs80 and vs13 ) libraries from ./make folder. \
  Or run command 'make' from folder with corresponding platform 
 
###INSTALLATION:  
  All you need to use library after building is to set NMPP enviroment variable. It is automaticly set by installer or 
  you can do it manually by 'make install' from ./make folder.
 
###REQUIREMENTS:  
  1. (for Windows) Installed GNU make . http://gnuwin32.sourceforge.net/packages/make.htm  
     Dowloand [Gnu make installer](http://gnuwin32.sourceforge.net/downlinks/make.php)  
    Note: You should use GNU **make** only. Microsoft **nmake** cannot parse attached makefiles 
  2. Installed NeuroMatrix SDK . Check for new version at http://www.module.ru/mb7707/toolchains-neuromatrix/
  3. Installed GnuWin32 utils  (Optional). Recommended for building of examples  http://sourceforge.net/projects/unxutils/ 
  4. Board SDK: (necessary  to build examples)
    - mc5103sdk (MC5103 Board support SDK)
    - mc7601sdk (MC7601 Board support SDK)
    - mb7707sdk (MB77.07 Board support SDK)  
    *Is is assumed that board drivers installed by user*
  4. (Optional) Installed Gnu GCC. Recommended for header dependency parcing build gcc-version of library build of gcc-examples http://www.mingw.org/
  5. (Optional) Installed Visual Studio 8  [Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)
  6. (Optional) Installed Visual Studio 13 [Visual Studio 2013 Express](https://www.microsoft.com/en-US/download/details.aspx?id=44914)  
  
>For version compatibility and path settings it is recomended to download and locally install [2-4] components at once by next commands from **/deps** folder
```bat
make download 
make install
```
**NOTE!** If enviroment variables like **NEURO, MC5103 , MB7707** defined by **?=** in **setenv.mk** then system value would be used , othewise (by **=**) they will be overrided by local pathes!  
By swithcing between **?=** and **=** you can select what SDK installaition to use (system or local).

 
###WARNING:  
  GCC-version builds will be skipped if 'CROSS_COMPILE' enviroment variable is not defined in your system.  
  Where 'CROSS_COMPILE' variable should contain prefix of your GCC cross-compiler.  
  VS80-version build will be skipped if 'VS80COMNTOOLS'  enviroment variable is not defined in your system.   
  VS13-version build will be skipped if 'VS120COMNTOOLS' enviroment variable is not defined in your system.   
  
  
###EXAMPLES:  
Each library component contains several examples in /app/examples  
Each example can be built for different targets.  
There are next supported targets:  
  NM6405 emulator  
  MC5103 board  
  M77601 board  
  MB7707 board (Specify MAC-address of your Ethernet adapter in /app/templates/sometest/make_mb7707/Makefile )  
  x86(gcc)  host  
  x86(vs80) host   
  x86(vs13) host  

  Run command 'make examples' to generate makefiles and build all examples  
  Run command 'make run'      to run all examples  
  Run command 'make kill'     to delete all generated makefiles, binary and temporary files  

  
WARNING:  
  Building and running of examples for some targets may be skipped if appropriate  
  enviroment variable ('MC5103','MB7707','MC7601','VS80COMNTOOLS','VS120COMNTOOLS','CROSS_COMPILE') 
  containing path to according SDK  is not defined in your system.
  
STRUCTURE OF LIBRARY:  

NMPP    
¦    
+---app                         -Applications    
¦   +---examples                   -Folder with examples  
¦   ¦   +---nmplc                      - Scalar library usage examples  
¦   ¦   ¦   +---Fixpoint32  
¦   ¦   ¦   ¦   +---make_emu             - build for emulator  
¦   ¦   ¦   ¦   +---make_mb7707          - build for MB7707  
¦   ¦   ¦   ¦   L---make_mc5103          - build for MC5103  
¦   ¦   ¦   L---Sqrt64  
¦   ¦   ¦       +---make_emu  
¦   ¦   ¦       +---make_mb7707  
¦   ¦   ¦       L---make_mc5103  
.....  
¦   ¦   +---nmpli                     - Image processing library usage examples  
¦   ¦   ¦   +---IMG_Filter_32s32s  
¦   ¦   ¦   ¦   +---make_emu               - build for emulator  
¦   ¦   ¦   ¦   +---make_gcc               - build for x86 by gcc   
¦   ¦   ¦   ¦   +---make_mb7707            - build for MB7707  
¦   ¦   ¦   ¦   +---make_mc5103            - build for MC5103  
¦   ¦   ¦   ¦   L---make_vs80              - build for Microsoft Visual Studio 8.0  
¦   ¦   ¦   ¦   L---make_vs13              - build for Microsoft Visual Studio 13.0  
¦   ¦   ¦   +---IMG_Filter_8s16s  
.....  
¦   ¦   +---nmplm                    - Matrix processing library usage examples  
¦   ¦   ¦   +---Inverse  
¦   ¦   ¦   ¦   +---make_emu  
¦   ¦   ¦   ¦   +---make_gcc  
¦   ¦   ¦   ¦   +---make_mb7707  
¦   ¦   ¦   ¦   +---make_mc5103  
¦   ¦   ¦   ¦   L---make_vs80  
¦   ¦   ¦   ¦   L---make_vs13  
¦   ¦   ¦   L---Simple  
.....  
¦   ¦   +---nmpls                    - Signal processing library usage examples  
¦   ¦   ¦   +---FFT  
¦   ¦   ¦   ¦   L---FFT256  
¦   ¦   ¦   ¦   ¦    +---make_emu  
¦   ¦   ¦   ¦   ¦    +---make_gcc  
¦   ¦   ¦   ¦   ¦    +---make_mb7707  
¦   ¦   ¦   ¦   ¦    +---make_mc5103  
¦   ¦   ¦   ¦   ¦    L---make_vs80  
¦   ¦   ¦   ¦   ¦    L---make_vs13  
.....  
¦   ¦   ¦   +---Filter  
¦   ¦   ¦   ¦   +---SIG_Filter_16s16s  
.....  
¦   ¦   ¦   ¦   +---SIG_Filter_16s32s  
.....  
¦   ¦   +---nmplv                   - Vector processing library usage examples  
¦   ¦   ¦   +---Simple  
.....  
¦   ¦   L---nmvcore                 - Vector core function usage exmaples  
¦   ¦       L---VecMulC  
¦   ¦           +---make_emu  
¦   ¦           +---make_mb7707  
¦   ¦           L---make_mc5103  
.....  
¦   +---templates                   - Temaplates for example projects generation  
¦   ¦   L---sometest  
¦   ¦       +---make_emu  
¦   ¦       +---make_gcc  
¦   ¦       +---make_mb7707  
¦   ¦       +---make_mc5103  
¦   ¦       +---make_mc7601  
¦   ¦       L---make_vs80  
....  
+---doc                             - Documentation folder  
+---include                         - Header folder  
¦   +---nmplc                            - scalar functions  
¦   +---nmpli                            - image  functions    
¦   +---nmplm                            - matrix functions  
¦   +---nmpls                            - signal functions  
¦   +---nmplv                            - vector functions  
¦   +---nmtl                             - templates functions  
¦   L---nmvcore                          - vector core function  
+---lib                            - Library folder  
¦   +---libnmpp_gcc.a                 - emulation library compiled by GNU GCC(mingw32)  
¦   +---nmpp_nmc3.lib                 - NeuroMatrix Core3 compatible library (Release)  
¦   +---nmpp_nmc3d.lib                - NeuroMatrix Core3 copatibale library (Debug)  
¦   +---nmpp_vs80.lib                 - emulation library compiled by Microsoft Visual Studio 8.0 (Release)  
¦   L---nmpp_vs80d.lib                - emulation library compiled by Microsoft Visual Studio 8.0 (Debug)  
¦   +---nmpp_vs13.lib                 - emulation library compiled by Microsoft Visual Studio 13.0 (Release)  
¦   L---nmpp_vs13d.lib                - emulation library compiled by Microsoft Visual Studio 13.0 (Debug)  
  
+---make                           - Make folder  
¦   +---distrib                        
¦   +---doxy                           
¦   +---nmc3                           - library project for NMSDK/NMC3 architecture  
¦   L---pc  
¦       +---gcc                        - library project for GNU GCC for x86  
¦       L---vs80                       - library project for Visual Studio 8.0 for x86  
¦       L---vs13                       - library project for Visual Studio 13.0 for x86  
L---src                           - Sources  
    +---nmplc                        - Scalar   
	...  
    +---nmpli                        - Image  
    ¦   +---Convert  
    ¦   ¦   +---common                  - NM&PC source folder  
    ¦   ¦   +---nm                      - NM source only  
    ¦   ¦   L---pc                      - PC source only  
    ...  
    +---nmplm                        - Matrix  
    +---nmpls                        - Signal  
    +---nmplv                        - Vector  
    L---nmvcore                      - Vector core   
          


FEEDBACK:  
Please send comments, suggestions, and bug reports to Sergey Mushkaev<mushkaev@module.ru>


