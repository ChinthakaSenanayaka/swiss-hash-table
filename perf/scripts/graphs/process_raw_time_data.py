import os

langNames = ["c", "cpp/basic", "cpp/swiss", "cs", "java", "python"]
opNames = ["insert", "search", "delete"]
insertFuncNames = ["testInsert1", "testInsert81922"]
searchFuncNames = ["testSearch1", "testSearch81922"]
deleteFuncNames = ["testDelete1", "testDelete81922"]

def deleteFile(file_path):
    if os.path.exists(file_path):
        try:
            os.remove(file_path)
        except OSError as e:
            print(f"Error deleting file '{file_path}': {e}")

def createFolder(file_path):
    directory = os.path.dirname(file_path)
    if not os.path.exists(directory):
        os.makedirs(directory)

def processRawDataFiles(rawDataFileName, inFolderName, outFolderName):
    for opName in opNames:
        funcNames = []
        if(opName == "insert"):
            funcNames = insertFuncNames
        elif (opName == "search"):
            funcNames = searchFuncNames
        elif (opName == "delete"):
            funcNames = deleteFuncNames
        
        for funcName in funcNames:
            fileNameNoExt = rawDataFileName.replace(".txt", "")
            outFileNameWithPath = outFolderName+'/'+opName+'/'+funcName+"/"+fileNameNoExt+".csv"
            deleteFile(outFileNameWithPath)
            createFolder(outFileNameWithPath)
            
            inFile = open(inFolderName+'/'+rawDataFileName)
            content = inFile.readlines()
            counter=1
            outFile = open(outFileNameWithPath, "a")
            for line in content:
                if(opName in line and funcName in line):
                    lineTexts = line.split()
                    # outFile.write(str(counter) + "," + fileNameNoExt + ",")
                    outFile.write(lineTexts[len(lineTexts)-2])
                    outFile.write("\n")
                    counter=counter+1

                # print(line)
            outFile.close()
            inFile.close()

for langName in langNames:
    inFolderName = "build/perf/graphs/raw/" + langName
    outFolderName = "build/perf/graphs/processed/" + langName

    for testRoundNo in range(20):
        rawDataFileName = "logs" + str(testRoundNo+1) + ".txt"
        processRawDataFiles(rawDataFileName, inFolderName, outFolderName)

print("===== Completed =====")