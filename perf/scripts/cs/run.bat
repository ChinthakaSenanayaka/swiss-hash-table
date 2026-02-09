@REM Author: Chinthaka Senanayaka
@REM Year: 2025

mkdir -p build\perf\cs\time\out
del build\perf\cs\time\out\logs.txt

@REM Run the C# code
cd perf\cs\time

dotnet run

cd ..\..\..