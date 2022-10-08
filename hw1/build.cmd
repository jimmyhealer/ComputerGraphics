@echo off
g++ %1.cpp -o %1.exe -lfreeglut -lopengl32 -lglu32 && (
  %1
)