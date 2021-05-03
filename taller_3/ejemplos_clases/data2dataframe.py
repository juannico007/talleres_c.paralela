import re
import os
import pandas as pd

names = os.listdir('./csv_results/')
print(names)

def createDataframe():
    processes = re.compile(r'\d+')
    files = []
    nprocesses = []
    
    for name in names:
        nprocesses.append(processes.findall(name)[-1])
                       
    computingData = pd.read_csv("./csv_results/" + names[0])

    computingData['nprocesses'] = [int(nprocesses[0])] * len(computingData)
    for f, i in zip(names[1:],range(1,len(names))):
        print(f)
        computingDataTmp = pd.read_csv("./csv_results/" + f) 

        computingDataTmp['nprocesses'] = [int(nprocesses[i])] * len(computingDataTmp)
        computingData = pd.concat([computingData, computingDataTmp])


    realColumnNames = []
    for colnames in computingData.columns:
        realColumnNames.append(colnames.strip(' '))
    computingData.columns = realColumnNames

    computingData.sort_values(by=['nprocesses', 'reps'], inplace = True, ascending = True)
    computingData.reset_index(inplace = True)
    computingData.drop(["index"], axis = 1, inplace = True)
    return computingData



print(createDataframe())



