import os

langNames = ["c", "cpp/swiss", "cpp/basic", "python", "java", "cs"]
langNameTexts = {"c": "C", "cpp/swiss": "CPP-Swiss", "cpp/basic": "CPP-Basic", "python": "Python", "java": "Java", "cs": "C#"}
opNames = ["insert", "search", "delete"]
insertFuncNames = ["testInsert1", "testInsert81922"]
searchFuncNames = ["testSearch1", "testSearch81922"]
deleteFuncNames = ["testDelete1", "testDelete81922"]

graphTypes1 = ["total", "min", "max", "avg"]
graphTypes81922 = ["total", "1-cumulative", "20-cumulative", "avg", "avg-cumulative", "min", "min-cumulative", "max", "max-cumulative"]

def createFolder(file_path):
    directory = os.path.dirname(file_path)
    if not os.path.exists(directory):
        os.makedirs(directory)

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

            outFolderName = "build/perf/graphs/analytics/"+opName+'/'+funcName+"/"
            createFolder(outFolderName)

            total1OutFileName = "total.csv"
            min1OutFileName = "minmaxavg.csv"
            total1OutText = "Element,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20\n"
            min1OutText = "Element,Min,Max,Avg\n"

            total81922OutFileName = "total.csv"
            oneCumu81922OutFileName = "1-cumulative.csv"
            twentyCumu81922OutFileName = "20-cumulative.csv"
            minCumu81922OutFileName = "min-cumulative.csv"
            maxCumu81922OutFileName = "max-cumulative.csv"
            avgCumu81922OutFileName = "avg-cumulative.csv"
            maxminCumu81922OutFileName = "max-min-cumulative.csv"
            total81922OutText = "Element,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20\n"
            oneCumu81922OutText = "Element"
            twentyCumu81922OutText = "Element"
            minCumu81922OutText = "Element"
            maxCumu81922OutText = "Element"
            avgCumu81922OutText = "Element"
            maxminCumu81922OutText = "Element"
            for lineNo in range(1, 1000001):
                oneCumu81922OutText += ","+str(lineNo)
                twentyCumu81922OutText += ","+str(lineNo)

                minCumu81922OutText += ","+str(lineNo)
                maxCumu81922OutText += ","+str(lineNo)
                avgCumu81922OutText += ","+str(lineNo)
                maxminCumu81922OutText += ","+str(lineNo)
            oneCumu81922OutText += "\n"
            twentyCumu81922OutText += "\n"
            minCumu81922OutText += "\n"
            maxCumu81922OutText += "\n"
            avgCumu81922OutText += "\n"
            maxminCumu81922OutText += "\n"

            for langName in langNames:
                langNameText = langNameTexts[langName]
                inFolderName = "build/perf/graphs/processed/"+langName+'/'+opName+'/'+funcName

                inFile = open(inFolderName+'/out.csv')
                fileContentLines = inFile.readlines()
                if funcName.endswith("1"):
                    dataLine = fileContentLines[1]
                    total1OutText += langNameText+","+dataLine
                    
                    dataVals = dataLine.split(",")
                    dataValsList = list(map(float, dataVals))
                    min1OutText += langNameText+","+str(min(dataValsList))+","+str(max(dataValsList))+","+str(sum(dataValsList)/len(dataValsList))+"\n"
                else:
                    list0, list1, list2, list3, list4, list5, list6, list7, list8, list9 = [], [], [], [], [], [], [], [], [], []
                    list10, list11, list12, list13, list14, list15, list16, list17, list18, list19 = [], [], [], [], [], [], [], [], [], []
                    total81922OutText += langNameText
                    
                    for lineNo in range(1, 1000001):
                        dataLine = fileContentLines[lineNo]
                        dataVals = dataLine.split(",")
                        list0.append(float(dataVals[0])), list1.append(float(dataVals[1])), list2.append(float(dataVals[2])), list3.append(float(dataVals[3])), list4.append(float(dataVals[4])), list5.append(float(dataVals[5]))
                        list6.append(float(dataVals[6])), list7.append(float(dataVals[7])), list8.append(float(dataVals[8])), list9.append(float(dataVals[9])), list10.append(float(dataVals[10]))
                        list11.append(float(dataVals[11])), list12.append(float(dataVals[12])), list13.append(float(dataVals[13])), list14.append(float(dataVals[14])), list15.append(float(dataVals[15]))
                        list16.append(float(dataVals[16])), list17.append(float(dataVals[17])), list18.append(float(dataVals[18])), list19.append(float(dataVals[19]))
                    total81922OutText += \
                        ","+str(sum(list0))+","+str(sum(list1))+","+str(sum(list2))+","+str(sum(list3))+","+str(sum(list4))+\
                        ","+str(sum(list5))+","+str(sum(list6))+","+str(sum(list7))+","+str(sum(list8))+","+str(sum(list9))+\
                        ","+str(sum(list10))+","+str(sum(list11))+","+str(sum(list12))+","+str(sum(list13))+","+str(sum(list14))+\
                        ","+str(sum(list15))+","+str(sum(list16))+","+str(sum(list17))+","+str(sum(list18))+","+str(sum(list19))+"\n"
                    
                    oneCumuVal = 0.0
                    twentyCumuVal = 0.0
                    oneCumu81922OutText += langNameText
                    twentyCumu81922OutText += langNameText

                    minCumuVal = 0.0
                    maxCumuVal = 0.0
                    avgCumuVal = 0.0
                    minCumu81922OutText += langNameText
                    maxCumu81922OutText += langNameText
                    avgCumu81922OutText += langNameText
                    maxminCumu81922OutText += langNameText+"-Max"

                    for lineNo in range(1, 1000001):
                        dataLine = fileContentLines[lineNo]
                        dataVals = dataLine.split(",")
                        oneCumuVal += float(dataVals[0])
                        oneCumu81922OutText += ","+str(oneCumuVal)
                        twentyCumuVal += float(dataVals[19])
                        twentyCumu81922OutText += ","+str(twentyCumuVal)

                        dataValsList = list(map(float, dataVals))
                        minCumuVal += min(dataValsList)
                        maxCumuVal += max(dataValsList)
                        avgCumuVal += sum(dataValsList)/len(dataValsList)
                        minCumu81922OutText += ","+str(minCumuVal)
                        maxCumu81922OutText += ","+str(maxCumuVal)
                        avgCumu81922OutText += ","+str(avgCumuVal)
                        maxminCumu81922OutText += ","+str(maxCumuVal)

                    oneCumu81922OutText += "\n"
                    twentyCumu81922OutText += "\n"
                    minCumu81922OutText += "\n"
                    maxCumu81922OutText += "\n"
                    avgCumu81922OutText += "\n"
                    maxminCumu81922OutText += "\n"

                    maxminCumu81922OutText += langNameText+"-Min"

                    for lineNo in range(1, 1000001):
                        dataLine = fileContentLines[lineNo]
                        dataVals = dataLine.split(",")

                        dataValsList = list(map(float, dataVals))
                        minCumuVal += min(dataValsList)
                        maxminCumu81922OutText += ","+str(minCumuVal)
                    
                    maxminCumu81922OutText += "\n"
                inFile.close()

            if funcName.endswith("1"):
                outFile = open(outFolderName+total1OutFileName, "w+")
                outFile.write(total1OutText)
                outFile.close()

                outFile = open(outFolderName+min1OutFileName, "w+")
                outFile.write(min1OutText)
                outFile.close()
            else:
                outFile = open(outFolderName+total81922OutFileName, "w+")
                outFile.write(total81922OutText)
                outFile.close()

                # outFile = open(outFolderName+oneCumu81922OutFileName, "w+")
                # outFile.write(oneCumu81922OutText)
                # outFile.close()
                # outFile = open(outFolderName+twentyCumu81922OutFileName, "w+")
                # outFile.write(twentyCumu81922OutText)
                # outFile.close()

                # outFile = open(outFolderName+minCumu81922OutFileName, "w+")
                # outFile.write(minCumu81922OutText)
                # outFile.close()
                # outFile = open(outFolderName+maxCumu81922OutFileName, "w+")
                # outFile.write(maxCumu81922OutText)
                # outFile.close()
                outFile = open(outFolderName+avgCumu81922OutFileName, "w+")
                outFile.write(avgCumu81922OutText)
                outFile.close()

                # outFile = open(outFolderName+maxminCumu81922OutFileName, "w+")
                # outFile.write(maxminCumu81922OutText)
                # outFile.close()

processRawDataFiles()

print("===== Completed =====")