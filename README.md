# [NMPP](https://github.com/RC-MODULE/nmpp)

# ������������:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM(ZIP):  http://rc-module.github.io/nmpp/nmpp.zip  
  CHM:  http://rc-module.github.io/nmpp/nmpp.chm (��� �������� ���������� ����� ������� "������ ���������� ��� �������� ����� �����")  
  PDF:  http://rc-module.github.io/nmpp/nmpp.pdf  

# ����������  
  NMPP (Neuro Matrix Performance Primitives) - C/C++ ���������� ���������� ��� ����������� NeuroMatrix.
  �������� ���������������� ������� ��� ������ �� ���������, ���������, ���������, ��������� � �������������.
  ������������ ��� ������������� ���������� � 1,2,4,8,16,32,64-���������� ������� ����������� ��������� NMC3,
  ��� � ���������� � ��������� ������ ��������� � ������� �������� ��� ���������� NMC4. 

# ���������� ����������  
  NMPP ���������� �������� � ���� ��������� ����������:  
  - nmvcore- ������������� �������������� ��������� ������� � ����������� ����������� �������� ����������
  - nmppc  - ��������� �������
  - nmppv  - ������� ������ � ���������
  - nmppm  - ������� ������ � ���������
  - nmpps  - ������� ��������� ��������
  - nmppi  - ������� ��������� ����������� 

  
# ������ �������� ���������:  
- ������� **NMC3/NMC4** ���������� ��� NM�GCC ���������:  
 
 |����������/���������   |1879��1�| 6406| 6407(int)| 6407(fpu)| 6408|
 |-----------------------|--------|-----|----------|----------|-----|
 |/lib/libnmpp-nmc3.a    |+       |   + |          |          |     |
 |/lib/libnmpp-nmc4.a    |        |     |+         |          |     |
 |/lib/libnmpp-nmc4f.a   |        |     |          |+         |+    |

  
- ������� **NMC3/NMC4** ���������� ��� ���������� (legacy) ����������:    

 |����������/���������   |1879��1�| 6406| 6407(int)| 6407(fpu)| 6408|
 |-----------------------|--------|-----|----------|-----|
 |/lib/nmpp-nmc3.lib     |   +    |   + |          |     |
 |/lib/nmpp-nmc3d.lib    |   +    |   + |          |     |
 |/lib/nmpp-nmc4.lib     |        |     |+         |     |     |
 |/lib/nmpp-nmc4d.lib    |        |     |+         |     |     |
 |/lib/nmpp-nmc4f.lib    |        |     |          |+    | +   |
 |/lib/nmpp-nmc4fd.lib   |        |     |          |+    | +   |

 

- **x86/x64** ��������� nmc-��������� �� ��:   
  /lib/libnmpp-x86.a - compiled by GNU GCC  
  /lib/nmpp-x86.lib  - (Release) compiled by Microsoft Visual Studio  
  /lib/nmpp-x86d.lib - (Debug)   compiled by Microsoft Visual Studio  
  
- **ARM** ���������� ����� NMC ������� �� ������� ARM-���� ���������� rpc (��� ������ �� ��������� � ARM �����):  
  /lib/libnmpp-arm-rpc.a
  
> **d**  ������� Debug ������ ����������


# ��������� NMPP 
## ��������� ����������
*  ������ ��������� (����������� lib-����������, �����, �������) ��������� �� ��������� �������� Makefile. ��� ����������� ������� ��������� Makefile-��  ��� Windows ��������� ������������� GNU **make**.
��� �� Windows ������������� ������ make 3.81  (3.82- ��������� ���� �����������). make 3.81 - ������ � ������ [GnuWin32-lite](https://github.com/RC-MODULE/gnuwin32-lite) (��.����)

* ��� ����������� ������ ���������������� Makefile-�� (������/��������/��������� �������� � .�.�.), � ����� �����-������������� ������ Makefile ��� � �� Windows, ��� � � Linux  ������������ UNIX-������� (rm,cp,which,...).  � ����� �� Windows ���������� �� ������� �� ������ [GnuWin](http://gnuwin32.sourceforge.net/), � ���� ���� ��������� �� ��������������� ���������. 
����������� ����������� �������� ���� ����������� GnuWin ������ �������: make,cmake,gzip � ��. ����� ���������� � ������� online-����������� [GnuWin32-lite](https://github.com/RC-MODULE/gnuwin32-lite)

* NeuroMatrix NMGCC-SDK  
  ��� ������ ��������� gcc ������������ ��� NeuroMatrix 

* Leqacy NeuroMatrix SDK  (���������� ������ SDK)
  ��� ������ ��������� ��� NeuroMatrix ��������� NMSDK ������� �� ���� 3.07

* x86/x64 SDK   
  ��� �������� NeuroMatrix ������� �� ������� NMPP ��� x86/x64 �������� ������ ��������� � �������   Gnu GCC.  http://www.mingw.org/  ��� http://win-builds.org/doku.php ��� Microsoft Visual Studio, � � ��������� �������� Express:  
[Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)  
[Visual Studio Express](https://visualstudio.microsoft.com/ru/vs/older-downloads/)  


 

## ������ NeuroMatrix ���������  GCC  ������������ 
  ������ �������������� �������� ```make``` �� ��������������� ����������� ����� */make/nmpp_archictecture*. 
  
```
nmpp> cd make/nmpp-nmc3
nmpp/make/nmpp-nmc3> make 
nmpp/make/nmpp-nmc3> make DEBUG=y
```
## ������ NeuroMatrix ��������� Legacy  ������������ 
  ������ ��������� ������������ �������������� �������� ```make``` � ������ ```legacy``` �� ��������������� ����������� ����� */make/nmpp_archictecture*. 
  
```
nmpp> cd make/nmpp-nmc3
nmpp/make/nmpp-nmc3> make legacy
nmpp/make/nmpp-nmc3> make legacy DEBUG=y
```

## ������ x86/x64 ���������  
  ��������� ����� �������� �c������������ ���������� **premake**.  
 ���������������� ������ ����� ��������   
 
```\nmpp\make\nmpp-x86-x64> make vs8 ```  
```\nmpp\make\nmpp-x86-x64> make vs14 ```  
��� � ������� ������:  vs8, vs12, vs12x64, vs12x64, unix, mingw ...
����������� ��������� ����������   
## ��������� ���������� ���������  
��� �������� ����������� ��������� � ����������� �������� ������������� ������������ ���������� ��������� **NMPP**. ������� ���������� **NMPP** � ��������� �� ���� � ������������� ����� NMPP ����� � ������� �������  ```make install``` �� ����� *./make*.

��������� ����������, ����������� ���� � ������������ �������������� � ����� */global.mk* �������� ���������� NMPP. ���� ���������� ��������� , ������ � ������������ ���������� **?=** , �� ���������� � �������, �� ��� ����� ��������� �� ��������� ���� � ����� /deps 
 

  
  
## EXAMPLES:  
Each library component contains several examples in *./app/examples*.
Each example can be built for different targets.  

There are next supported targets:
 - NM6405 emulator  
 - MC12101 board  
 - MC5103 board  
 - M77601 board  
 - MB7707 board (Specify MAC-address of your Ethernet adapter in /app/templates/sometest/make_mb7707/Makefile )  
 - x86(gcc) host  
 - x86(vs)  host   
 

List of actual target platforms is specified by **PLATFORMS** variable in **global.mk**.
Action of **global.mk** may be overriden by **local.mk** if exists.

  Run  **make** command from *./app/examples* folder to generate Makefiles and build all examples  
  Run  **make run**  command    to run all examples  
  Run  **make kill** command     to delete all generated Makefiles, binary and temporary files  

  
>WARNING:  
  Building and running of examples for some targets may be skipped if appropriate environment    variable (**VS80COMNTOOLS**,**VS120COMNTOOLS**,**CROSS_COMPILE**)
  containing path to according SDK  is not defined in your system.

## TESTS:  
Running tests is performed by execution and comparision of results on different target paltforms:
```bat
  cd /app/test
  make configure
  make 
  make test TARGET1=mc5103 TARGET2=vs8
```
Macro PLATFORMS in ./global.mk defines list of platforms for which tests need to be compiled.
```bat
PLATFORMS = vs8 mc5103 emu6405 mc7601 mb7707_libload
```

## STRUCTURE OF LIBRARY:  
```bat
NMPP    
�    
+---app                         -Applications    
�   +---examples                   -Folder with examples  
�   �   +---nmplc                      - Scalar library usage examples  
�   �   �   +---Fixpoint32  
�   �   �   �   +---make_emu             - build for emulator  
�   �   �   �   +---make_mb7707          - build for MB7707  
�   �   �   �   L---make_mc5103          - build for MC5103  
�   �   �   L---Sqrt64  
�   �   �       +---make_emu  
�   �   �       +---make_mb7707  
�   �   �       L---make_mc5103  
.....  
�   �   +---nmpli                     - Image processing library usage examples  
�   �   �   +---IMG_Filter_32s32s  
�   �   �   �   +---make_emu               - build for emulator  
�   �   �   �   +---make_gcc               - build for x86 by gcc   
�   �   �   �   +---make_mb7707            - build for MB7707  
�   �   �   �   +---make_mc5103            - build for MC5103  
�   �   �   �   L---make_vs8              - build for Microsoft Visual Studio 8.0  
�   �   �   �   L---make_vs13              - build for Microsoft Visual Studio 13.0  
�   �   �   +---IMG_Filter_8s16s  
.....  
�   �   +---nmplm                    - Matrix processing library usage examples  
�   �   �   +---Inverse  
�   �   �   �   +---make_emu  
�   �   �   �   +---make_gcc  
�   �   �   �   +---make_mb7707  
�   �   �   �   +---make_mc5103  
�   �   �   �   L---make_vs8  
�   �   �   �   L---make_vs13  
�   �   �   L---Simple  
.....  
�   �   +---nmpls                    - Signal processing library usage examples  
�   �   �   +---FFT  
�   �   �   �   L---FFT256  
�   �   �   �   �    +---make_emu  
�   �   �   �   �    +---make_gcc  
�   �   �   �   �    +---make_mb7707  
�   �   �   �   �    +---make_mc5103  
�   �   �   �   �    L---make_vs8  
�   �   �   �   �    L---make_vs13  
.....  
�   �   �   +---Filter  
�   �   �   �   +---SIG_Filter_16s16s  
.....  
�   �   �   �   +---SIG_Filter_16s32s  
.....  
�   �   +---nmplv                   - Vector processing library usage examples  
�   �   �   +---Simple  
.....  
�   �   L---nmvcore                 - Vector core function usage exmaples  
�   �       L---VecMulC  
�   �           +---make_emu  
�   �           +---make_mb7707  
�   �           L---make_mc5103  
.....  
�   +---templates                   - Temaplates for example projects generation  
�   �   L---sometest  
�   �       +---make_emu  
�   �       +---make_gcc  
�   �       +---make_mb7707  
�   �       +---make_mc5103  
�   �       +---make_mc7601  
�   �       L---make_vs8  
....  
+---doc                             - Documentation folder  
+---include                         - Header folder  
�   +---nmplc                            - scalar functions  
�   +---nmpli                            - image  functions    
�   +---nmplm                            - matrix functions  
�   +---nmpls                            - signal functions  
�   +---nmplv                            - vector functions  
�   +---nmtl                             - templates functions  
�   L---nmvcore                          - vector core function  
+---lib                            - Library folder  
�   +---libnmpp_gcc.a                 - emulation library compiled by GNU GCC(mingw32)  
�   +---nmpp_nmc3.lib                 - NeuroMatrix Core3 compatible library (Release)  
�   +---nmpp_nmc3d.lib                - NeuroMatrix Core3 copatibale library (Debug)  
�   +---nmpp_x86.lib                 - emulation library compiled by Microsoft Visual Studio (Release)  
�   L---nmpp_x86d.lib                - emulation library compiled by Microsoft Visual Studio  (Debug)  
�
+---make                           - Make folder  
�   +---distrib                        
�   +---doxy                           
�   +---nmc3                           - library project for NMSDK/NMC3 architecture  
�   +---nmpp-x86-x64                   - cmake folder to generate  x86 library  with GNU GCC  / Visual Studio 8.0/  Visual Studio 13.0 ...
�
L---src                           - Sources  
    +---nmplc                        - Scalar   
	...  
    +---nmpli                        - Image  
    �   +---Convert  
    �   �   +---common                  - NM&PC source folder  
    �   �   +---nm                      - NM source only  
    �   �   L---pc                      - PC source only  
    ...  
    +---nmplm                        - Matrix  
    +---nmpls                        - Signal  
    +---nmplv                        - Vector  
    L---nmvcore                      - Vector core   
```


## �������� �����:  
����������� , ������� , ���������  ����� ���������� ��  Sergey Mushkaev <mushkaev@module.ru>


