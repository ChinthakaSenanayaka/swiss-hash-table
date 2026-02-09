@REM Author: Chinthaka Senanayaka
@REM Year: 2025

mkdir -p build\perf\cpp\basic
mkdir -p build\perf\cpp\basic\time\out
del build\perf\cpp\basic\time\out\logs.txt

@REM ============================Basic CPP HT===========================================

echo "Processing basic C++"
call build.bat
@REM Generate project's make files
cd build\perf\cpp\basic\time
cmake ..\..\..\..\..\perf\cpp\basic\time

@REM Compile the C++ code
cmake --build .

@REM Run the C++ code
@ECHO OFF
for %%f in (..\..\..\..\..\perf\cpp\basic\time\*.cc) do (
    Debug\%%~nf
)

cd ..\..\..\..\..

@REM ============================Basic CPP HT===========================================

mkdir -p build\perf\cpp\swiss
mkdir -p build\perf\cpp\swiss\time\out
del build\perf\cpp\swiss\time\out\logs.txt

@REM ============================Swiss CPP HT===========================================

echo "Processing Swiss C++"
@REM Generate project's make files
cd build\perf\cpp\swiss\time
cmake ..\..\..\..\..\perf\cpp\swiss\time\ -DCMAKE_PREFIX_PATH=%HOMEDRIVE%%HOMEPATH%\deps\abseil_out\

@REM Compile the C++ code
cmake --build .

@REM Run the C++ code
@ECHO OFF
for %%f in (..\..\..\..\..\perf\cpp\swiss\time\*.cc) do (
    Debug\%%~nf
)

cd ..\..\..\..\..

@REM ============================Swiss CPP HT===========================================