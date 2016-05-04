echo Begin build cpp support library for new compiler >cppnew.log
for %%i in (*.asm) do nmcc %%i -O0 -Snolink >>cppnew.log
for %%i in (*.cpp) do nmcc %%i -O0 -Snolink >>cppnew.log
libr -c cppnew.lib *.elf >>cppnew.log
del *.elf >nul
echo Begin build cpp support library for new compiler >cppnew05.log
for %%i in (*.asm) do nmcc -nmc3 %%i -O0 -Snolink >>cppnew05.log
for %%i in (*.cpp) do nmcc -nmc3 %%i -O0 -Snolink >>cppnew05.log
libr -c cppnew05.lib *.elf >>cppnew05.log
del *.elf >nul
