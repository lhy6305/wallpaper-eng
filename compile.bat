@echo off
del /f /q 1.dll
g++ -shared 1.cpp -o 1.dll||pause
