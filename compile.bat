:: Convience Script for Compilation,
:: Includes SFML Include, and links to sfml-*-d
C:\mingw64\bin\clang++ main.cpp -IC:\libs\SFML\Clang\include -LC:\libs\SFML\Clang\lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -o bin/sfml_program.exe
@echo off
cd bin
csimulator.exe
cd ..