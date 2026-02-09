#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

PROCESSOR_TYPE=$1

# Run all the performance scripts (excluding C#) together with 1 seconds pauses to cool down.

rm -r ./build/perf/graphs/raw/* 2>/dev/null
mkdir -p build/perf/graphs/raw/c/
mkdir -p build/perf/graphs/raw/cpp/basic/
mkdir -p build/perf/graphs/raw/cpp/swiss/
mkdir -p build/perf/graphs/raw/cs/
mkdir -p build/perf/graphs/raw/java/
mkdir -p build/perf/graphs/raw/python/

for i in $(seq 1 20)
do
    echo "Round number: $i"

    chmod 777 ./perf/scripts/c/run.sh
    ./perf/scripts/c/run.sh $PROCESSOR_TYPE
    sleep 1
    mv build/perf/c/time/out/logs.txt build/perf/c/time/out/logs$i.txt
    mv build/perf/c/time/out/logs$i.txt build/perf/graphs/raw/c/
done

for i in $(seq 1 20)
do
    echo "Round number: $i"

    chmod 777 ./perf/scripts/cpp/run.sh
    ./perf/scripts/cpp/run.sh
    sleep 1
    mv build/perf/cpp/basic/time/out/logs.txt build/perf/cpp/basic/time/out/logs$i.txt
    mv build/perf/cpp/basic/time/out/logs$i.txt build/perf/graphs/raw/cpp/basic/
    mv build/perf/cpp/swiss/time/out/logs.txt build/perf/cpp/swiss/time/out/logs$i.txt
    mv build/perf/cpp/swiss/time/out/logs$i.txt build/perf/graphs/raw/cpp/swiss/
done

for i in $(seq 1 20)
do
    echo "Round number: $i"

    chmod 777 ./perf/scripts/java/run.sh
    ./perf/scripts/java/run.sh
    sleep 1
    mv build/perf/java/time/out/logs.txt build/perf/java/time/out/logs$i.txt
    mv build/perf/java/time/out/logs$i.txt build/perf/graphs/raw/java/
done

for i in $(seq 1 20)
do
    echo "Round number: $i"

    chmod 777 ./perf/scripts/python/run.sh
    ./perf/scripts/python/run.sh
    sleep 1
    mv build/perf/python/time/out/logs.txt build/perf/python/time/out/logs$i.txt
    mv build/perf/python/time/out/logs$i.txt build/perf/graphs/raw/python/
done

for i in $(seq 1 20)
do
    echo "Round number: $i"

    chmod 777 ./perf/scripts/cs/run.sh
    ./perf/scripts/cs/run.sh
    sleep 1
    mv build/perf/cs/time/out/logs.txt build/perf/cs/time/out/logs$i.txt
    mv build/perf/cs/time/out/logs$i.txt build/perf/graphs/raw/cs/
done

rm -r ./build/perf/graphs/processed/* 2>/dev/null
mkdir -p build/perf/graphs/processed/c/
mkdir -p build/perf/graphs/processed/cpp/basic/
mkdir -p build/perf/graphs/processed/cpp/swiss/
mkdir -p build/perf/graphs/processed/cs/
mkdir -p build/perf/graphs/processed/java/
mkdir -p build/perf/graphs/processed/python/
python3 perf/scripts/graphs/process_raw_time_data.py
python3 perf/scripts/graphs/summarize_processed_time_data.py

rm -r ./build/perf/graphs/analytics/* 2>/dev/null
mkdir -p build/perf/graphs/analytics/c/
mkdir -p build/perf/graphs/analytics/cpp/basic/
mkdir -p build/perf/graphs/analytics/cpp/swiss/
mkdir -p build/perf/graphs/analytics/cs/
mkdir -p build/perf/graphs/analytics/java/
mkdir -p build/perf/graphs/analytics/python/
python3 perf/scripts/graphs/organize_summarized_data_to_csv.py

rm -r ./perf/charts/* 2>/dev/null
mkdir -p "perf/charts/insert/1 round/"
mkdir -p "perf/charts/insert/20 rounds/"
mkdir -p "perf/charts/search/1 round/"
mkdir -p "perf/charts/search/20 rounds/"
mkdir -p "perf/charts/delete/1 round/"
mkdir -p "perf/charts/delete/20 rounds/"
python3 perf/scripts/graphs/generate_graphs_for_csv.py