@echo off

@if not "%MINGW_ROOT%" == "" (@set "PATH=%PATH%;%MINGW_ROOT%")

cd .

if "%1"=="" ("C:\PROGRA~1\POLYSP~1\R2019b\bin\win64\gmake"  -f AD_Vect_low_izm_dif_modes_subsyst.mk all) else ("C:\PROGRA~1\POLYSP~1\R2019b\bin\win64\gmake"  -f AD_Vect_low_izm_dif_modes_subsyst.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
