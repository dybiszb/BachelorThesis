@echo off
if not exist "%~dp0/results/" mkdir "%~dp0/results"
set filename=%~dp0\results\test_%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.txt
%~dp0unit_tests.exe > %filename%
type %filename%
ECHO Results saved in: %filename%
PAUSE