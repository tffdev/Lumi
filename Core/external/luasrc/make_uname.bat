@echo off
REM This builds all the libraries of the folder for 1 uname

call tecmake %1 %2 %3 %4 %5 %6 %7 %8

if "%1"==""          goto end
if "%1"=="mingw6"    goto luaexe
if "%1"=="mingw6_64" goto luaexe
if "%1"=="cygw211"    goto luaexe
if "%1"=="vc10"      goto luaexe
if "%1"=="vc10_64"   goto luaexe
if "%1"=="all"       goto lua_all
goto end

:lua_all
call make_uname mingw6
call make_uname mingw6_64
call make_uname cygw211
goto end

:luaexe
call tecmake %1 "MF=lua" %2 %3 %4 %5 %6 %7
call tecmake %1 "MF=wlua" %2 %3 %4 %5 %6 %7
call tecmake %1 "MF=luac" %2 %3 %4 %5 %6 %7
if "%1"=="mingw6"    copy /Y ..\lib\dllw6\*.dll* ..\bin\Win32\
if "%1"=="mingw6_64" copy /Y ..\lib\dllw6_64\*.dll* ..\bin\Win64\
if "%1"=="cygw211"    copy /Y ..\lib\cygw211\*.dll ..\bin\cygw211\
if "%1"=="vc10"      copy /Y ..\lib\dll10\*.dll* ..\bin\Win32\
if "%1"=="vc10_64"   copy /Y ..\lib\dll10_64\*.dll* ..\bin\Win64\
goto end

:end
