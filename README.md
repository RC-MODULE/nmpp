# [NMPP](https://github.com/RC-MODULE/nmpp)

# Документация:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM:  http://rc-module.github.io/nmpp/nmpp.chm  
  PDF:  http://rc-module.github.io/nmpp/nmpp.pdf  

# Назначение  
  NMPP (Neuro Matrix Performance Primitives) - C/C++ библиотека примитивов для архитектуры NeuroMatrix.
  Содержит оптимизированные функции для работы со скалярами, векторами, матрицами, сигналами и изображениями.
  Поддерживает как целочисленную арифметику с 1,2,4,8,16,32,64-разрядными даннами процессоров семейства NMC3,
  так и арифметику с плавающей точкой одинарной и двойной точности для процессора NMC4. 

# Компоненты библиотеки  
  NMPP библиотека включает в себя следующие компоненты:  
  - nmvcore- универсальные низкоуровневые векторные функции с регистровым интерфейсом передачи параметров
  - nmppc  - скалярные функции
  - nmppv  - функции работы с векторами
  - nmppm  - функции работы с матрицами
  - nmpps  - функции обработки сигналов
  - nmppi  - функции обработки изображений 

  
# Состав бинарных библиотек:  
- Целевые **NMC3/NMC4** библиотеки:  
  /lib/nmpp-nmc3.lib   (Release)   :NM6405,NM6406,soc
  /lib/nmpp-nmc3d.lib  (Debug)     :NM6405,NM6406,soc
  /lib/nmpp-nmc4.lib   (Release)   :NM6407 NMC1 (Fixed point)
  /lib/nmpp-nmc4d.lib  (Debug)     :NM6407 NMC1 (Fixed point)
  /lib/nmpp-nmc4f.lib   (Release)  :NM6407 NMC0 (FPU)
  /lib/nmpp-nmc4fd.lib  (Debug)    :NM6407 NMC0 (FPU)
 
- **x86/x64** эмуляторы nmc-библиотек на ПК:   
  /lib/libnmpp-x86.a - compiled by GNU GCC 
  /lib/nmpp-x86.lib  - (Release) compiled by Microsoft Visual Studio
  /lib/nmpp-x86d.lib - (Debug)   compiled by Microsoft Visual Studio
  
- **ARM** библиотека вызов NMC функций со стороны ARM-ядра средствами rpc (для систем на кристалле с ARM ядром):  
  /lib/libnmpp-arm-rpc.a
  


# Установка NMPP 
## Системные требования
*  Сборка компонент (статические lib-библиотеки, тесты, примеры) построена на сборочных скриптах Makefile. Для корректного запуска сборочных Makefile-ов  под Windows требуется установленный GNU **make**.
Для ОС Windows рекомендуется версия make 3.81  (3.82- проявляет себя нестабильно). make 3.81 - входит в состав [GnuWin32-lite](https://github.com/RC-MODULE/gnuwin32-lite) (см.ниже)

* Для обеспечения полной функциональности Makefile-ов (тестов/примеров/генерации проектов и .т.д.), а также кросс-платформенной работы Makefile как в ОС Windows, так и в Linux  используются UNIX-утилиты (rm,cp,which,...).  В среде ОС Windows вызываются их аналоги из пакета [GnuWin](http://gnuwin32.sourceforge.net/), в виду чего требуется их предварительная установка. 
Сокращенный необходимый комплект всех необходимых GnuWin утилит включая: make,cmake,gzip и пр. можно установить с помощью online-установщика [GnuWin32-lite](https://github.com/RC-MODULE/gnuwin32-lite)
* NeuroMatrix SDK  
  Для сборки библиотек под NeuroMatrix требуется NMSDK версией не ниже 3.07

* x86/x64 SDK   
  Для эмуляции NeuroMatrix функций из состава NMPP под x86/x64 возможна сборка библиотек с помощью   Gnu GCC.  http://www.mingw.org/  или http://win-builds.org/doku.php или Microsoft Visual Studio, и в частности версиями Express:  
[Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)  
[Visual Studio 2013 Express](https://www.microsoft.com/en-US/download/details.aspx?id=44914)  


 

## Сборка NeuroMatrix библиотек  
  Сборка осуществляется командой ```make``` из соответствующей архитектуре папки */make/nmpp_archictecture*. 
  
```
nmpp> cd make/nmpp-nmc3
nmpp/make/nmpp-nmc3> make 
nmpp/make/nmpp-nmc3> make DEBUG=y
```
## Сборка x86/x64 библиотек  
  Генерация самих проектов оcуществляется средствами **cmake**.  
 Сконфигурировать проект можно командой   
```\nmpp\make\nmpp-x86-x64> make vs8 ```  
```\nmpp\make\nmpp-x86-x64> make vs14 ```  
где с помощью ключей:  vs8, vs12, vs12x64, vs12x64, unix, mingw ...
указывается требуемый компилятор   
## Настройка переменных окружения  
Для удобства подключения библиотек к собственным проектам рекомендуется использовать переменную окружения **NMPP**. Создать переменную **NMPP** и присвоить ей путь к установленной папке NMPP можно с помощью команды  ```make install``` из папки *./make*.

## Зависимости  
Для сборки примеров и тестов могут потребоваться некоторые дополнительные средства разработки, визуализации, системные и прикладные библиотеки. За установку комплекта ПО зависимостей отвечает  online-установщик [dev-kit](https://github.com/RC-MODULE/dev-kit)
Необходимые зависимости для данного проекта NMPP можно скачать и установить локально в папке */deps* командой:
* Вариант A:

```bat
 nmpp/deps> make download
 nmpp/deps> make install
```
>в случае proxy-авторизации необходимо установить переменные:
```
nmpp/deps>set  http_proxy=http://username:password@proxy:port/  
nmpp/deps>set https_proxy=http://username:password@proxy:port/
```

* Вариант B:  
либо  ```install.bat ``` c возможностью диалоговой proxy аутентификацией

> в состав зависимостей также включено системное ПО плат и само NMSDK. Установка этих компонент не модифицирует системных переменных окружения, не влияет на возможно ранее установленное ПО  и служит в целях совместимости и соответствия версий ПО. 


Настройка переменных, указывающих пути к зависимостям осуществляется в файле */global.mk* корневой директории NMPP. Если переменные окружения , идущие с конструкцией присвоения **?=** , не определены в системе, то они будут настроены на локальные пути к папке /deps 
 

  
  
## EXAMPLES:  
Each library component contains several examples in *./app/examples*.
Each example can be built for different targets.  

There are next supported targets:
 - NM6405 emulator  
 - MC5103 board  
 - M77601 board  
 - MB7707 board (Specify MAC-address of your Ethernet adapter in /app/templates/sometest/make_mb7707/Makefile )  
 - x86(gcc)  host  
 - x86(vs8) host   
 - x86(vs13) host  

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
¦   ¦   ¦   ¦   L---make_vs8              - build for Microsoft Visual Studio 8.0  
¦   ¦   ¦   ¦   L---make_vs13              - build for Microsoft Visual Studio 13.0  
¦   ¦   ¦   +---IMG_Filter_8s16s  
.....  
¦   ¦   +---nmplm                    - Matrix processing library usage examples  
¦   ¦   ¦   +---Inverse  
¦   ¦   ¦   ¦   +---make_emu  
¦   ¦   ¦   ¦   +---make_gcc  
¦   ¦   ¦   ¦   +---make_mb7707  
¦   ¦   ¦   ¦   +---make_mc5103  
¦   ¦   ¦   ¦   L---make_vs8  
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
¦   ¦   ¦   ¦   ¦    L---make_vs8  
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
¦   ¦       L---make_vs8  
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
¦   +---nmpp_x86.lib                 - emulation library compiled by Microsoft Visual Studio (Release)  
¦   L---nmpp_x86d.lib                - emulation library compiled by Microsoft Visual Studio  (Debug)  
¦
+---make                           - Make folder  
¦   +---distrib                        
¦   +---doxy                           
¦   +---nmc3                           - library project for NMSDK/NMC3 architecture  
¦   +---nmpp-x86-x64                   - cmake folder to generate  x86 library  with GNU GCC  / Visual Studio 8.0/  Visual Studio 13.0 ...
¦
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


## Обратная связь:  
Предложения , вопросы , замечания  можно направлять на  Sergey Mushkaev <mushkaev@module.ru>


