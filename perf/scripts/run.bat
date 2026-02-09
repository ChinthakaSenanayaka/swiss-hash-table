@REM Author: Chinthaka Senanayaka
@REM Year: 2025

@REM Run all the performance scripts together with 1 seconds pauses to cool down.

mkdir -p build\perf\graphs\raw\c\
mkdir -p build\perf\graphs\raw\cpp\basic\
mkdir -p build\perf\graphs\raw\cpp\swiss\
mkdir -p build\perf\graphs\raw\cs\
mkdir -p build\perf\graphs\raw\java\
mkdir -p build\perf\graphs\raw\python\

@echo off
FOR /L %%N IN (1, 1, 20) DO (
    echo Round number: %%N

    call perf\scripts\c\run.ba INTEL
    timeout /t 1
    ren build\perf\c\time\out\logs.txt logs%%N.txt
    move build\perf\c\time\out\logs%%N.txt build\perf\graphs\raw\c\
)

FOR /L %%N IN (1, 1, 20) DO (
    echo Round number: %%N

    call perf\scripts\cpp\run.bat
    timeout /t 1
    ren build\perf\cpp\basic\time\out\logs.txt logs%%N.txt
    move build\perf\cpp\basic\time\out\logs%%N.txt build\perf\graphs\raw\cpp\basic\
    ren build\perf\cpp\swiss\time\out\logs.txt logs%%N.txt
    move build\perf\cpp\swiss\time\out\logs%%N.txt build\perf\graphs\raw\cpp\swiss\
)

FOR /L %%N IN (1, 1, 20) DO (
    echo Round number: %%N

    call perf\scripts\cs\run.bat
    timeout /t 1
    ren build\perf\cs\time\out\logs.txt logs%%N.txt
    move build\perf\cs\time\out\logs%%N.txt build\perf\graphs\raw\cs\
)

FOR /L %%N IN (1, 1, 20) DO (
    echo Round number: %%N

    call perf\scripts\java\run.bat
    timeout /t 1
    ren build\perf\java\time\out\logs.txt logs%%N.txt
    move build\perf\java\time\out\logs%%N.txt build\perf\graphs\raw\java\
)

FOR /L %%N IN (1, 1, 20) DO (
    echo Round number: %%N
    
    call perf\scripts\python\run.bat
    timeout /t 1
    ren build\perf\python\time\out\logs.txt logs%%N.txt
    move build\perf\python\time\out\logs%%N.txt build\perf\graphs\raw\python\
)

del build\perf\graphs\processed\*
mkdir -p build\perf\graphs\processed\c\
mkdir -p build\perf\graphs\processed\cpp\basic\
mkdir -p build\perf\graphs\processed\cpp\swiss\
mkdir -p build\perf\graphs\processed\cs\
mkdir -p build\perf\graphs\processed\java\
mkdir -p build\perf\graphs\processed\python\
python3 perf\scripts\graphs\process_raw_time_data.py
python3 perf\scripts\graphs\summarize_processed_time_data.py

del build\perf\graphs\analytics\*
mkdir -p build\perf\graphs\analytics\c\
mkdir -p build\perf\graphs\analytics\cpp\basic\
mkdir -p build\perf\graphs\analytics\cpp\swiss\
mkdir -p build\perf\graphs\analytics\cs\
mkdir -p build\perf\graphs\analytics\java\
mkdir -p build\perf\graphs\analytics\python\
python3 perf\scripts\graphs\organize_summarized_data_to_csv.py

del perf\charts\*
mkdir -p "perf\charts\insert\1 round\"
mkdir -p "perf\charts\insert\20 rounds\"
mkdir -p "perf\charts\search\1 round\"
mkdir -p "perf\charts\search\20 rounds\"
mkdir -p "perf\charts\delete\1 round\"
mkdir -p "perf\charts\delete\20 rounds\"
python3 perf\scripts\graphs\generate_graphs_for_csv.py