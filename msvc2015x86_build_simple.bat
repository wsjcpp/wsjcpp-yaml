@echo off

endlocal
setlocal enabledelayedexpansion

pushd %~dp0
set SCRIPT_DIR=%CD%
popd

call "%VS140COMNTOOLS%..\..\VC\bin\x86_amd64\vcvarsx86_amd64.bat"

echo ====== msbuild version ======
msbuild -version
echo =============================

echo CMake configuring...
cmake -H. -Btmp\windows -G "Visual Studio 14 2015" -DCMAKE_BUILD_TYPE=Release > win-build.log 2>&1
if %ERRORLEVEL% GEQ 1 (
    echo Failed cmake prepare configuration. Log of build look in file win-build.log
    EXIT /B 1
)
echo Done.

echo Building...
cmake --build tmp\windows --config Release >> win-build.log 2>&1
if %ERRORLEVEL% GEQ 1 (
    echo Failed cmake build. Log of build look in file win-build.log
    EXIT /B 1
)
echo Done.

endlocal