DOCUMENTATION:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM: http://rc-module.github.io/nmpp/nmpp.chm  
  PDF: http://rc-module.github.io/nmpp/nmpp.pdf  

DESCRIPTION:
  NMPP is "Neuro Matrix Performance Primitives" library 
  which consists of scalar, vector-matrix  , signal and 
  image processing functions for Neuro Matrix architecture. 

COMPONENTS:
  NMPP library contains next components:
  -nmvcore- basic low-level vector-cooprocessor functions 
  -nmplc  - scalar functions
  -nmplv  - vector functions
  -nmplm  - matrix functions
  -nmpls  - signal processing functions
  -nmpli  - image  processing functions

  
ARCHITECTURE:
nmpp-libary supports nmc3-core processor family : NM6405,NM6406, and SOCs
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

BUILDING LIBRARY:
  Run command 'make' to build all (nmc3, gcc , vs80 and vs13 ) libraries from ./make folder. \
  Or run command 'make' from folder corresponding to platform 
 
INSTALLATION:
  All you need to use library is to set NMPP enviroment variable. It is automaticly set by installer or 
  you can do it manually by 'make install' from ./make folder.
 
REQUIREMENTS:
  1. Installed NeuroMatrix SDK . Check for new version at http://www.module.ru/mb7707/toolchains-neuromatrix/
  2. Installed GNU make. http://gnuwin32.sourceforge.net/packages/make.htm  
    Note: You should use GNU 'make' only. Microsoft 'nmake' cannot parse attached makefiles 
  3. Installed GnuWin32 utils (Optional) recommended for building of examples  http://sourceforge.net/projects/unxutils/
  4. Installed Gnu GCC        (Optional) recommended for header dependency parcing/ build gcc-version of library/ build of gcc-examples http://www.mingw.org/
  5. Installed Visual Studio 8/13(Optional)
  
  For Windows system you can install all-in-one package (including 2,3): gnuwin32-nmsdk-pack.exe  . http://www.module.ru/mb7707/NeuroMatrix/gnuwin32-nmsdk-pack.exe

WARNING:
  GCC-version builds will be skipped if 'CROSS_COMPILE' enviroment variable is not defined in your system. 
  Where 'CROSS_COMPILE' variable should contain prefix of your GCC cross-compiler.
  VS80-version build will be skipped if 'VS80COMNTOOLS'  enviroment variable is not defined in your system. 
  VS13-version build will be skipped if 'VS120COMNTOOLS' enviroment variable is not defined in your system. 
  
  
EXAMPLES:
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
│
├───app                         -Applications
│   ├───examples                   -Folder with examples
│   │   ├───nmplc                      - Scalar library usage examples
│   │   │   ├───Fixpoint32
│   │   │   │   ├───make_emu             - build for emulator
│   │   │   │   ├───make_mb7707          - build for MB7707
│   │   │   │   └───make_mc5103          - build for MC5103
│   │   │   └───Sqrt64
│   │   │       ├───make_emu
│   │   │       ├───make_mb7707
│   │   │       └───make_mc5103
.....
│   │   ├───nmpli                     - Image processing library usage examples
│   │   │   ├───IMG_Filter_32s32s
│   │   │   │   ├───make_emu               - build for emulator
│   │   │   │   ├───make_gcc               - build for x86 by gcc 
│   │   │   │   ├───make_mb7707            - build for MB7707
│   │   │   │   ├───make_mc5103            - build for MC5103
│   │   │   │   └───make_vs80              - build for Microsoft Visual Studio 8.0
│   │   │   │   └───make_vs13              - build for Microsoft Visual Studio 13.0
│   │   │   ├───IMG_Filter_8s16s
.....
│   │   ├───nmplm                    - Matrix processing library usage examples
│   │   │   ├───Inverse
│   │   │   │   ├───make_emu
│   │   │   │   ├───make_gcc
│   │   │   │   ├───make_mb7707
│   │   │   │   ├───make_mc5103
│   │   │   │   └───make_vs80
│   │   │   │   └───make_vs13
│   │   │   └───Simple
.....
│   │   ├───nmpls                    - Signal processing library usage examples
│   │   │   ├───FFT
│   │   │   │   └───FFT256
│   │   │   │   │    ├───make_emu
│   │   │   │   │    ├───make_gcc
│   │   │   │   │    ├───make_mb7707
│   │   │   │   │    ├───make_mc5103
│   │   │   │   │    └───make_vs80
│   │   │   │   │    └───make_vs13
.....
│   │   │   ├───Filter
│   │   │   │   ├───SIG_Filter_16s16s
.....
│   │   │   │   ├───SIG_Filter_16s32s
.....
│   │   ├───nmplv                   - Vector processing library usage examples
│   │   │   ├───Simple
.....
│   │   └───nmvcore                 - Vector core function usage exmaples
│   │       └───VecMulC
│   │           ├───make_emu
│   │           ├───make_mb7707
│   │           └───make_mc5103
.....
│   ├───templates                   - Temaplates for example projects generation
│   │   └───sometest
│   │       ├───make_emu
│   │       ├───make_gcc
│   │       ├───make_mb7707
│   │       ├───make_mc5103
│   │       ├───make_mc7601
│   │       └───make_vs80
....
├───doc                             - Documentation folder
├───include                         - Header folder
│   ├───nmplc                            - scalar functions
│   ├───nmpli                            - image  functions  
│   ├───nmplm                            - matrix functions
│   ├───nmpls                            - signal functions
│   ├───nmplv                            - vector functions
│   ├───nmtl                             - templates functions
│   └───nmvcore                          - vector core function
├───lib                            - Library folder
│   ├───libnmpp_gcc.a                 - emulation library compiled by GNU GCC(mingw32)
│   ├───nmpp_nmc3.lib                 - NeuroMatrix Core3 compatible library (Release)
│   ├───nmpp_nmc3d.lib                - NeuroMatrix Core3 copatibale library (Debug)
│   ├───nmpp_vs80.lib                 - emulation library compiled by Microsoft Visual Studio 8.0 (Release)
│   └───nmpp_vs80d.lib                - emulation library compiled by Microsoft Visual Studio 8.0 (Debug)
│   ├───nmpp_vs13.lib                 - emulation library compiled by Microsoft Visual Studio 13.0 (Release)
│   └───nmpp_vs13d.lib                - emulation library compiled by Microsoft Visual Studio 13.0 (Debug)

├───make                           - Make folder
│   ├───distrib                      
│   ├───doxy                         
│   ├───nmc3                           - library project for NMSDK/NMC3 architecture
│   └───pc
│       ├───gcc                        - library project for GNU GCC for x86
│       └───vs80                       - library project for Visual Studio 8.0 for x86
│       └───vs13                       - library project for Visual Studio 13.0 for x86
└───src                           - Sources
    ├───nmplc                        - Scalar 
	...
    ├───nmpli                        - Image
    │   ├───Convert
    │   │   ├───common                  - NM&PC source folder
    │   │   ├───nm                      - NM source only
    │   │   └───pc                      - PC source only
    ...
    ├───nmplm                        - Matrix
    ├───nmpls                        - Signal
    ├───nmplv                        - Vector
    └───nmvcore                      - Vector core 
        


FEEDBACK:
Please send comments, suggestions, and bug reports to Sergey Mushkaev<mushkaev@module.ru>


