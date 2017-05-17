# ЗАПУСК ТЕСТОВОЙ РЕГРЕССИИ

## ЗАВИСИМОСТИ:  

Необходимое установленное SDK и ПО:   
1. GnuWin32-lite https://github.com/RC-MODULE/gnuwin32-lite  
2. NMSDK и должна быть определена переменная окружения  NEURO  
3. ПО поддержки платы (МЦ121.01, МЦ51.03, МВ77.07...) и должна быть определена соответствующая переменная окружения (MC12101,MC5103,MB7707...)
4. библиотека nm_io для вывода printf  и должна быть определена переменная окружения NM_IO  
5. nmserver - клиент-сервер для удаленной работы с платой (МЦ121.01  или МЦ51.03)

Установить последнее  NMSDK и ПО поддержки плат можно скачав online-установщик
https://github.com/RC-MODULE/dev-kit  и далее командой **install** выполнить установку, например:
```
d:\GIT\dev-kit> install.bat install-nmsdk
d:\GIT\dev-kit> install.bat install-mc12101sdk
d:\GIT\dev-kit> install.bat install-nm_io
d:\GIT\dev-kit> install.bat nmserver
```

либо одной командой
```
d:\GIT\dev-kit> install.bat install-nmsdk install-mc12101sdk install-nm_io nmserver
```
компоненты будут распакованы локально в d:\GIT\dev-kit>

префикс "install-" означает, что соответствующий пакет будет распакован с установкой (модификацией)
соответствующих переменных окружения (NEURO, MC12101 , NM_IO, PATH ...)

Если без префикса  "install-", то будет произведена только распаковка , без модификации переменных окружения.



Должен быть установлен Visual Studio 2005 либо gcc (MinGW)

Установка MinGW может быть осуществлена также через install.bat :
```
d:\GIT\dev-kit> install.bat mingw
```
Скачаются необходимые gcc-пакеты и запустится установщик.
После появления диалогового окна , указать путь к директории с пакетами /dev-kit/1.5.0 и путь установки, как показано http://win-builds.org/doku.php/download_and_installation_from_windows  
Далее необходимо самостоятельно прописать путь к gcc в PATH.


## СБОРКА NMPP:  

- Собрать библиотеку nmpp-nmc4f.lib:
d:\GIT\nmpp\make\nmpp-nmc4f> make
должна собраться d:\GIT\nmpp\lib\nmpp-nmc4f.lib

Собрать библиотеку nmpp под ПК (варианты а,б):
- a) Собрать библиотеку nmpp-x86.a под ПК  c помощью gcc:
d:\GIT\nmpp\make\nmpp-x86-x64> make gcc
должна собраться d:\GIT\nmpp\lib\libnmpp-x86.a

- б). Собрать библиотеку nmpp-x86.lib под ПК  c помощью VisualStudio 2005:
d:\GIT\nmpp\make\nmpp-x86-x64> make vs8
должна собраться d:\GIT\nmpp\lib\nmpp-x86.lib




## 9. КОНФИГУРИРОВАНИЕ ТЕСТОВ:
генерация сборочных проектов осуществляется командой:  
a) Для gcc:
```
d:\GIT\nmpp\app\test\nmpps_float>make configure PLATFORMS="gcc mc12101_nmc0"
```

б) для VS2005:
```
d:\GIT\nmpp\app\test\nmpps_float>make configure PLATFORMS="vs8 mc12101_nmc0"
```

В результате команды ``` make confogure``` под заданные платформы для всех тестов рекурсивно из  d:\GIT\nmpp\app\test\nmpps_float> будут созданы сборочные проекты. Т.е. рядом с каждым тестом должны появиться сборочные проекты, например:
d:\GIT\nmpp\app\test\nmpps_float\Arithmetic\nmppsAdd_32f\make_mc12101_nmc0
d:\GIT\nmpp\app\test\nmpps_float\Arithmetic\nmppsAdd_32f\make_vs8


Возможные платформы для выбора:  
для x86:  
 - gcc
 - vs8

для NMC:  
 - mc5103
 - mc7601
 - mc12101_nmc0    (ядро с плавающей точкой)
 - mc12101_nmc1    (ядро с целочисленной арифметикой)
 - emu6405


## 10. ЗАПУСК
Каждый тестовый запуск производит сравнение контрольных сумм от результатов выполнения одного теста, но на двух разных платформах (из x86 и NM)

Запуск всех тестов осуществляется командой:
```
d:\GIT\nmpp\app\test\nmpps_float>make test TARGET1=gcc TARGET2=mc12101_nmc0
```
либо в случае VisualStudio:
```
d:\GIT\nmpp\app\test\nmpps_float>make test TARGET1=vs8 TARGET2=mc12101_nmc0
```

Рекурсивным обходом будут запущенные все тесты из нижележащих поддиректорий.
Запуск может быть из любого места.

Если тест прошел выводится : TEST-OK!
Иначе выводится diff  от двух crc-контрольных сумм и тестовая регрессия останавливается


Настроить нужные или ненужные для тестирования директории можно в локальных файлах настроек, например:
d:\GIT\nmpp\app\test\nmpps_float\local.mk


Логи сохраняются в
d:\GIT\nmpp\app\test

команда ``` make clean ``` рекурсивно удаляет продукты сборки  
команда ``` make kill ``` рекурсивно удаляет все , кроме  cpp тестов

переменные  TARGET1,TARGET2,PLATFORMS можно задать по умолчанию в global.mk
и дальше просто использовать
```
make configure
make test
```