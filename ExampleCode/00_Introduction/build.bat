@echo off
echo %1
g++ %1.c -o %1.exe -lfreeglut -lopengl32 -lglu32
