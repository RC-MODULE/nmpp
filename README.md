# [NMPP](https://github.com/RC-MODULE/nmpp)

# Документация:  
  HTML: http://rc-module.github.io/nmpp/  
  CHM(ZIP):  http://rc-module.github.io/nmpp/nmpp.zip  
  CHM:  http://rc-module.github.io/nmpp/nmpp.chm (При открытии необходимо снять галочку "Всегда спрашивать при открытии этого файла")  
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

# Архитектуры 
  Поддерживаюся архитектуры NMC3 и NMC4.  Для NMC4 библиотеки разделяются по типу ядра: с плавающей точкой и целочисленной арифметикой.

- Поддерживаемые процессоры :
 |процессор/ядро   													|nmc3	| nmc4 	| nmc4f	| arm	|
 |------------------------------------------------------------------|-------|-------|-------|-------|
 |[1879ХБ1Я](https://www.module.ru/products/1/18791-2) 				|   +   |     	|       |   +   |
 |[К1879ВЯ1Я](https://www.module.ru/products/1/23-18791) 		 	|   +   |     	|       |   +   |
 |[К1888ВС018](https://www.module.ru/products/1/1888018-2) 		 	|   +   |     	|       |   +   |
 |[1879ВМ5(NM6406)](https://www.module.ru/products/1/3-18795) 		|   +   |     	|       |       |
 |[1879ВМ6Я(6407)](https://www.module.ru/products/1/81-18796)       |       |   + 	|   +   |       |
 |[1879ВМ8Я(6408)](https://www.module.ru/products/1/26-18798)       | 	    |       |   +   |   +   |
 


# Кроссплатформенность    
  Для отладки и прототипирования проектов на x86/64 архитектуре предоставляются эмуляционные библиотеки для Windows/Linux . 
  Библиотеки точно иммитируют исполнение функций для NeuroMatrix c побитовой точностью в x86/64-приложении .
  Функции имеют единый интерфейс и могут использоваться в кроссплатформенной (x86/NeuroMatrix) разработке приложений под Windows/Linux. 
  
  Также имеется  **ARM** библиотека осуществляющая  вызов NMC функций со стороны ARM-ядра средствами rpc (для систем на кристалле с ARM ядром):  
  /lib/libnmpp-arm-rpc.a
  В частности ,данная библиотека осуществляют взаимосвязь Matlab/Simulink с NeuroMatrix.

# Сборка 
  Под NeuroMatrix сборка соуществляется NMСGCC копилятором. Также поддерживается устаревший (legacy)  компилятор .
  Эммуляторы библиотк собираются через  VisualStudio/MinGW  под Windows и GCC в Linux .
  

# Установка NMPP 
## Системные требования
* NeuroMatrix NMGCC-SDK  
  Для сборки библиотек под NeuroMatrix  gcc компилятором 

* Leqacy NeuroMatrix SDK  (устаревшая версия SDK)
  Для сборки библиотек под NeuroMatrix предыдущим компилятором требуется  NMSDK версией не ниже 3.07

* x86/x64 SDK   
  Для эмуляции NeuroMatrix функций из состава NMPP под x86/x64 возможна сборка библиотек с помощью   Gnu GCC.  http://www.mingw.org/  или http://win-builds.org/doku.php или Microsoft Visual Studio, и в частности версиями Express:  
[Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)  
[Visual Studio Express](https://visualstudio.microsoft.com/ru/vs/older-downloads/)  

*  Сборка компонент (статические lib-библиотеки, тесты, примеры) построена на Makefile скриптах. Для корректного запуска сборочных Makefile-ов  под Windows требуется установленный GNU **make**.
Для ОС Windows рекомендуется версия make [3.81](https://sourceforge.net/projects/gnuwin32/files/make/3.81/)  (3.82- проявляет себя нестабильно). 

* Генерация сборочных проектов x86/x64 библиотек/тестов, в т.ч. для VisualStudio, осуществляется [premake5](https://premake.github.io/)  версией не ниже premake-5.0.0-alpha14

* Для обеспечения полной функциональности Makefile-ов (тестов/примеров/генерации проектов и .т.д.), а также кросс-платформенной работы Makefile как в ОС Windows, так и в Linux  используются :    UNIX-утилиты:   
[rm,cp,mkdir,rmdir,...](http://gnuwin32.sourceforge.net/packages/coreutils.htm )  
[find](http://gnuwin32.sourceforge.net/packages/findutils.htm ) (требует переимнования в gfind.exe для устранения конфликта
 с системным Windows\System32\find.exe)  

* Пути к premake5 и GnuWin утилитами должны быть прописаны в PATH 



## Сборка NeuroMatrix библиотек  GCC  компилятором 
  Сборка библиотек осуществляется командой ```make``` из соответствующей архитектуре папки */make/nmpp-\<archictecture\>* :  

| Команда 									| Собранная библиотека 	|
|-------------------------------------------|-----------------------|
|``` nmpp/make/nmpp-nmc3> make ```  		| nmpp/lib/libnmpp-nmc3.a  |
|``` nmpp/make/nmpp-nmc3> make DEBUG=y```	| nmpp/lib/libnmpp-nmc3d.a |
|``` nmpp/make/nmpp-nmc4> make ```  		| nmpp/lib/libnmpp-nmc4.a  |
|``` nmpp/make/nmpp-nmc4> make DEBUG=y```	| nmpp/lib/libnmpp-nmc4d.a |
|``` nmpp/make/nmpp-nmc4f> make ```  		| nmpp/lib/libnmpp-nmc4f.a |
|``` nmpp/make/nmpp-nmc4f> make DEBUG=y```	| nmpp/lib/libnmpp-nmc4f.a |
> **d** - признак Debug версии библиотеки  
> **f** - признак библиотеки для ядра с плавающей точкой . Если  без префикса - для целочисленного ядра.



## Сборка NeuroMatrix библиотек Legacy  компилятором 
  Сборка устаревшим компилятором возможна командой ```make``` с ключом ```legacy``` из соответствующей архитектуре папки */make/nmpp-\<archictecture\>*:   
| Команда 										| Собранная библиотека	  |
|-----------------------------------------------|-------------------------|
|```nmpp/make/nmpp-nmc3> make legacy```  		| nmpp/lib/nmpp-nmc3.lib  |
|```nmpp/make/nmpp-nmc3> make legacy DEBUG=y```	| nmpp/lib/nmpp-nmc3.lib  |
|```nmpp/make/nmpp-nmc4> make legacy```  		| nmpp/lib/nmpp-nmc4.lib  |
|```nmpp/make/nmpp-nmc4> make legacy DEBUG=y```	| nmpp/lib/nmpp-nmc4d.lib |
|```nmpp/make/nmpp-nmc4f> make legacy ```  		| nmpp/lib/nmpp-nmc4f.lib |
|```nmpp/make/nmpp-nmc4f> make legacy DEBUG=y```| nmpp/lib/nmpp-nmc4f.lib |


## Сборка x86/x64 библиотек  
  Генерация сборочных файлов/проектов для x86/64 рахитектуры в Windows/Linux оcуществляется средствами [**premake5**](https://premake.github.io/).  
Сконфигурировать проект  и собрать его можно одной из команд:   
| Команда 										| Собранная библиотека	  |
|-----------------------------------------------|-------------------------|
|``` nmpp\make\nmpp-x86-x64> make vs2015  ```	| nmpp\lib\nmpp-x86.lib   |
|												| nmpp\lib\nmpp-x86d.lib  | 
|												| nmpp\lib\nmpp-x64.lib   |
|												| nmpp\lib\nmpp-x64d.lib  |
|``` nmpp\make\nmpp-x86-x64> make gmake  ```	| nmpp\lib\nmpp-x86.lib (Windows)|   
|``` nmpp\make\nmpp-x86-x64> make gmake  ```	| nmpp/lib/libnmpp-x64.a (Linux)|   
 
> x86/x64 эмуляторы билиотек включают в себя функции как с плавающей арифметикой , так и с целочисленной. 

Возможные ключи ```make```:
| Ключ   | ОС      | Toolchain            |
|--------|---------|-----------------------|
| vs2005 | Windows | MS Visual Studio 2005 |
| vs2015 | Windows | MS Visual Studio 2015 |
| vs2017 | Windows | MS Visual Studio 2017 |
| gmake  | Windows | MinGW|
| gmake  | Linux   | GCC |



``` nmpp\make\nmpp-x86-x64> make vs2015  ```  
``` nmpp\make\nmpp-x86-x64> make vs2017  ```  
в результате будут собраны:   



В Linux/Windows возможна сборка через GCC/MinGW с помощью ключа ```gmake``` :


Возможные ключи :  vs2005, vs2015, vs2017 , gmake 

Команда ```  nmpp\make\nmpp-x86-x64> make ```  без ключа иниицрует сборку под VS2015 в Winodws и под GСС в Linux.

## Настройка переменных окружения  
Для удобства подключения библиотек к собственным проектам, а также к примерам и тестам  рекомендуется использовать переменную окружения **NMPP**. В Windows cоздать переменную **NMPP** и присвоить ей путь к установленной папке NMPP можно с помощью команды  
```\nmpp\make\> make setenv```


## Сборка примеров и тестов   
 Для сборки тестов и примеров  необходим [HAL](https://github.com/RC-MODULE/hal) со скомпилированными соотвествующими библиотеками и прописанной переменной окружения *HAL*.
 Некоторые тесты и примеров идут только с исходными С++ текстами. Сконфигурировать сборочные проекты пакетно можно командой ```make configure ``` из корневой папки с тестами или примерами, например:  

```\nmpp\app\test> make configure ```  
```\nmpp\app\examples-float> make configure ```  
  
Список платформ для которых будут сформированы сборочные проекты определяются перерменной PLATFORMS в global.mk или local.mk   
  
Сборка и запуск примера осуществляюется командами ```make ``` и ```make run ``` из соотвествующей папки */make_\<board_compiler\>*, например:  
```nmpp\> cd \app\examples\nmpps\nmppsAbs\make_mc12101_nmpu1-gcc-ld```   
```\> make```   
```\> make run ```   
 
  
  
## Примеры:  
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

## Тесты:  
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

## Структура каталогов :  
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


