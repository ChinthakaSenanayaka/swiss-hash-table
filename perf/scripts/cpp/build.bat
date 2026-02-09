@REM Author: Chinthaka Senanayaka
@REM Year: 2025

set currentPath=%cd%

@REM Installing program dependencies
rd /s /q %HOMEDRIVE%%HOMEPATH%\deps\*
mkdir -p %HOMEDRIVE%%HOMEPATH%\deps\abseil-cpp
git clone https://github.com/abseil/abseil-cpp.git %HOMEDRIVE%%HOMEPATH%\deps\abseil-cpp\
cd %HOMEDRIVE%%HOMEPATH%\deps\abseil-cpp
mkdir -p %HOMEDRIVE%%HOMEPATH%\deps\abseil_out
mkdir -p %HOMEDRIVE%%HOMEPATH%\deps\abseil-cpp\build
cd %HOMEDRIVE%%HOMEPATH%\deps\abseil-cpp\build
cmake .. -DCMAKE_INSTALL_PREFIX=%HOMEDRIVE%%HOMEPATH%\deps\abseil_out\
cmake --build . --target install

cd %currentPath%