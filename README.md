###DOCUMENTATION:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM: http://rc-module.github.io/nmpp/nmpp.chm  
  PDF: http://rc-module.github.io/nmpp/nmpp.pdf  

###DESCRIPTION:  
  NMPP is "Neuro Matrix Performance Primitives" C/C++ library 
  which consists of high-performance scalar, vector-matrix  , signal and 
  image processing functions for Neuro Matrix architecture. 
  NMPP-library supports nmc3-core processor family : NM6405,NM6406, and SOCs.  

    Current version : 1.1 (2016.04.21)
  
###COMPONENTS:  
  NMPP library contains next components:  
  - nmvcore- basic low-level vector-cooprocessor functions  
  - nmplc  - scalar functions  
  - nmplv  - vector functions  
  - nmplm  - matrix functions  
  - nmpls  - signal processing functions  
  - nmpli  - image  processing functions  

  
###LIBARY CONTENT :  
- Main **NMC3** librires:  
  /lib/nmpp_nmc3.lib   (Release)  
  /lib/nmpp_nmc3d.lib  (Debug)  
 
- x86 PC emulator libraries:   
  /lib/libnmpp_gcc.a  - compiled by GNU GCC under Windows  
  /lib/nmpp_vs80.lib  - (Release) compiled by Microsoft Visual Studio 8.0  
  /lib/nmpp_vs80d.lib - (Debug)  
  /lib/nmpp_vs13.lib  - (Release) compiled by Microsoft Visual Studio 13.0  
  /lib/nmpp_vs13d.lib - (Debug)  

  
###BUILDING LIBRARY:  
  Run **make** command to build all (nmc3, gcc , vs80 and vs13 ) libraries from *./make* folder.  Or run **make** from appropriate sub-folder.
 
###USAGE:  
  Use **NMPP** environment variable in your own projects to specify a location of library. 
  You can set **NMPP** variable manually to the path were it has been installed or by **make install** command from *./make* folder.



###REQUIREMENTS  

#### GENERAL REQUIREMENTS: 
  1. GnuWin32 utils installed. You need **make** ver 3.81 and other utilities from GnuWin32 package  to process 
     Makefile-s.  
#####A. Lite Gnuwin32 installation (Only utils needed for RC Module project building would be installed). It is fast installation, recommended.
	 Download [GnuWin32-lite](https://github.com/RC-MODULE/gnuwin32-lite/archive/master.zip) from https://github.com/RC-MODULE/gnuwin32-lite.  
	 After unziping open a command window, switch to the GnuWin32-lite directory and run download.bat.  
	 If you are behind proxy define your proxy settings in .\wget.ini or add environment variables **http_proxy** and **https_proxy**  to your system.
	 If download.bat completes successfully you will be able to run the installer with path where to install gnuwin32. 
	 For example: 
```bat
C:\gnuwin32-lite-mater>set  http_proxy=http://username:password@proxy:80/
C:\gnuwin32-lite-mater>set https_proxy=http://username:password@proxy:80/
C:\gnuwin32-lite-mater>download 
C:\gnuwin32-lite-mater>install C:\gnuwin32 
```
#####B. Full GnuWin32 Installation (All available utils would be enstalled [600MB] ) 
	 Download and install setup [GetGnuWin32-0.6.3.exe](http://downloads.sourceforge.net/project/getgnuwin32/getgnuwin32/0.6.30/GetGnuWin32-0.6.3.exe) from https://sourceforge.net/projects/getgnuwin32/?source=typ_redirect.  
	 After installation open a command window, switch to the GetGnuWin32 directory and run download.bat.  
	 If you are behind proxy define your proxy settings into .\bin\wget.ini or add environment variables **http_proxy** and **https_proxy**  to your system.
	 If download.bat completes successfully you will be able to run the installer. 
For example: 
```bat
C:\Users\Internet\Desktop>set  http_proxy=http://username:password@proxy:80/
C:\Users\Internet\Desktop>set https_proxy=http://username:password@proxy:80/

C:\Users\Internet\Desktop>cd getgnuwin32 
C:\Users\Internet\Desktop\GetGnuWin32>download 
C:\Users\Internet\Desktop\GetGnuWin32>install C:\gnuwin32 
```

Add installed GnuWin32\bin folder to the %PATH% environmnet variable.  

>  Don't use Gnu **make** ver-3.82 and Microsoft **nmake** - they don't  process provided Makefiles correctly

#### MAIN REQUIREMENTS TO BUILD NMC-LIBRARY:  
  2. Installed NeuroMatrix SDK  
  
#### ADDITIONAL SDK REQUIREMENTS FOR HOST-EMULATION LIBRARIES AND EXAMPLES:    
  3. Board SDK with installed drivers: (necessary  to build and run examples)
    - mc5103sdk (MC5103 Board support SDK)
    - mc7601sdk (MC7601 Board support SDK)
    - mb7707sdk (MB77.07 Board support SDK) + WinPCap  
  4. VSHELL - graphic shell
  5. Installed Visual Studio 8  [Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)
  6. Installed Visual Studio 13 [Visual Studio 2013 Express](https://www.microsoft.com/en-US/download/details.aspx?id=44914)  
  7. Installed Gnu GCC.  http://www.mingw.org/ 


	
####DOWNLOADING DEPENDENCIES
You can download and locally install all latest actual components (board SDKs, vshell, GnuWin32 utils) into */deps* folder by two commands from */deps* folder:
```bat
make download 
make install
```

It is recommended to download dependencies to prevent version mismatch between different components. It guaranties  successful compilation and running of examples.
No any variables would be created or modified in global system environment, so your NMPP installation would be fully standalone (except installed board drivers)
<!--
> FOR WINDOWS XP: PowerShell 2.0 is required to provide Internet downloading and unzipping by **make download** and **make install** commands . 
It is requried  PowerShell 2.0 or  installed
to provide Internet downloading and unpacking.

  To install Windows Powershell 2.0 on an XP machine, you must have Windows XP Service Pack 3 installed. Powershell is included in the Windows Management Framework which you can download at https://support.microsoft.com/ru-ru/kb/968929 .  
  Windows XP (KB968930) https://www.microsoft.com/ru-ru/download/details.aspx?id=16818
  [Microsoft .NET Framework 2.0 Service Pack 1 (x86)](https://www.microsoft.com/ru-RU/download/details.aspx?id=16614) may be also required.
  
  Installed Gnu GCC is recommended for header dependency parcing and build the gcc-version of library build of gcc-examples http://www.mingw.org/ -->

###WARNING:   
 - If environment variables like **NEURO, MC5103 , MB7707** defined using **?=** in **global.mk** then system value would be used (if exists), otherwise (using **=**) they will be overrided by local pathes!  
 By switching between **?=** and **=** you can select what SDK installation to use (system or local).
 
 - GCC-version build will be skipped if **CROSS_COMPILE** environment variable is not defined in your system.  Where **CROSS_COMPILE** variable should contain prefix of your GCC cross-compiler.  
 - VS80-version build will be skipped if **VS80COMNTOOLS**  environment variable is not defined in your system.   
 - VS13-version build will be skipped if **VS120COMNTOOLS** environment variable is not defined in your system.   
  
###EXAMPLES:  
Each library component contains several examples in *./app/examples*.
Each example can be built for different targets.  

There are next supported targets:
 - NM6405 emulator  
 - MC5103 board  
 - M77601 board  
 - MB7707 board (Specify MAC-address of your Ethernet adapter in /app/templates/sometest/make_mb7707/Makefile )  
 - x86(gcc)  host  
 - x86(vs80) host   
 - x86(vs13) host  

List of actual target platforms is specified by **PLATFORMS** variable in **global.mk**.
Action of **global.mk** may be overriden by **local.mk** if exists.

  Run  **make** command from *./app/examples* folder to generate Makefiles and build all examples  
  Run  **make run**  command    to run all examples  
  Run  **make kill** command     to delete all generated Makefiles, binary and temporary files  

  
>WARNING:  
  Building and running of examples for some targets may be skipped if appropriate environment    variable (**VS80COMNTOOLS**,**VS120COMNTOOLS**,**CROSS_COMPILE**)
  containing path to according SDK  is not defined in your system.
  
###STRUCTURE OF LIBRARY:  
```bat
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
```


###FEEDBACK:  
Please send comments, suggestions, and bug reports to Sergey Mushkaev <mushkaev@module.ru>


