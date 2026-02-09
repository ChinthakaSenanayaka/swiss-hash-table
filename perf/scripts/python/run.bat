@REM Author: Chinthaka Senanayaka
@REM Year: 2025

mkdir -p build\perf\python\time\out
del build\perf\python\time\out\logs.txt

@REM Run the Python code
@ECHO OFF
for %%f in (perf\python\time\*.py) do (
    python3 %%f
)