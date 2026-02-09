import os

langNames = ["c", "cpp/swiss", "cpp/basic", "python", "java", "cs"]
opNames = ["insert", "search", "delete"]
insertFuncNames = ["testInsert1", "testInsert81922"]
searchFuncNames = ["testSearch1", "testSearch81922"]
deleteFuncNames = ["testDelete1", "testDelete81922"]

def getMillis(strNum):
    strNumWONewline = strNum.replace("\n", "")
    return str(int(strNumWONewline) / 1000000)

def deleteFile(file_path):
    if os.path.exists(file_path):
        try:
            os.remove(file_path)
        except OSError as e:
            print(f"Error deleting file '{file_path}': {e}")

def processRawDataFiles():

    for opName in opNames:
        funcNames = []
        if(opName == "insert"):
            funcNames = insertFuncNames
        elif (opName == "search"):
            funcNames = searchFuncNames
        elif (opName == "delete"):
            funcNames = deleteFuncNames
    
        for funcName in funcNames:

            for langName in langNames:
                inFolderName = "build/perf/graphs/processed/"+langName+'/'+opName+'/'+funcName+"/"
                outFolderName = "build/perf/graphs/processed/"+langName+'/'+opName+'/'+funcName+"/"
                
                langDataforRound = []
                for roundNo in range(20):
                    rawDataFileName = "logs" + str(roundNo+1) + ".csv"

                    inFile = open(inFolderName+'/'+rawDataFileName)
                    langDataforRound.append(inFile.readlines())
                    inFile.close()

                dataForLang = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20\n"
                rangeVal = 1 if funcName.endswith("1") else 1000000
                for lineNo in range(rangeVal):
                    dataForLang += \
                        getMillis(langDataforRound[0][lineNo])+","+ \
                        getMillis(langDataforRound[1][lineNo])+","+ \
                        getMillis(langDataforRound[2][lineNo])+","+ \
                        getMillis(langDataforRound[3][lineNo])+","+ \
                        getMillis(langDataforRound[4][lineNo])+","+ \
                        getMillis(langDataforRound[5][lineNo])+","+ \
                        getMillis(langDataforRound[6][lineNo])+","+ \
                        getMillis(langDataforRound[7][lineNo])+","+ \
                        getMillis(langDataforRound[8][lineNo])+","+ \
                        getMillis(langDataforRound[9][lineNo])+","+ \
                        getMillis(langDataforRound[10][lineNo])+","+ \
                        getMillis(langDataforRound[11][lineNo])+","+ \
                        getMillis(langDataforRound[12][lineNo])+","+ \
                        getMillis(langDataforRound[13][lineNo])+","+ \
                        getMillis(langDataforRound[14][lineNo])+","+ \
                        getMillis(langDataforRound[15][lineNo])+","+ \
                        getMillis(langDataforRound[16][lineNo])+","+ \
                        getMillis(langDataforRound[17][lineNo])+","+ \
                        getMillis(langDataforRound[18][lineNo])+","+ \
                        getMillis(langDataforRound[19][lineNo])+"\n"
                
                outFilePath = outFolderName+"out.csv"
                deleteFile(outFilePath)
                outFile = open(outFilePath, "w")
                outFile.write(dataForLang)
                outFile.close()

processRawDataFiles()

print("===== Completed =====")