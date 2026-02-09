@REM Author: Chinthaka Senanayaka
@REM Year: 2025

mkdir -p build\perf\java\time\out
del build\perf\java\time\out\logs.txt

@REM Compile the Java code files
@ECHO OFF
for %%f in (perf\java\time\*.java) do (
    javac -cp build/perf/java/time/ -d build/perf/java/time/ %%f
)

@REM Run the Java files
@ECHO OFF
for %%f in (build\perf\java\time\*.class) do (
    java -cp build/perf/java/time/ %%~nf
)