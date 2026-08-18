@echo off

REM Deleting old files
del *.o *.exe *gcm.cache

REM Compiling files without linking
@echo Compiling files...
g++ -std=c++23 -fmodules-ts -c libSpace.cpp
g++ -std=c++23 -fmodules-ts -c main.cpp
pause

REM Linking Files
@echo Linking...
g++ -std=c++23 -fmodules-ts libSpace.o main.o -o main.exe

REM Run...
@echo Running...
main.exe 20 20
pause