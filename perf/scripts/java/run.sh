#!/bin/bash

# Author: Chinthaka Senanayaka
# Year: 2025

mkdir -p build/perf/java
mkdir -p build/perf/java/time/out
rm ./build/perf/java/time/out/logs.txt 2>/dev/null

java_v=("$(java -version)")
echo $java_v

# Compile the Java code files
javaFilesWithPath=$(find perf/java/time/ -name '*.java')
for javaFileWithPath in $javaFilesWithPath
do
    javac -cp build/perf/java/time/ -d build/perf/java/time/ $javaFileWithPath
done

# Run the Java files
classFilesWithPath=$(find build/perf/java/time/ -name '*.class' -not -path '*build/perf/java/time/Test*Util*')
for classFileWithPath in $classFilesWithPath
do
    classFile=$(basename $classFileWithPath)
    fileNameNoExt=("${classFile[@]%.class}")
    java -cp build/perf/java/time/ $fileNameNoExt
done