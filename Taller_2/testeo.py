import re
import os 
import pandas as pd

names = os.listdir('./')

def createDataframe():

    results_files = re.compile(r'result.*.csv')
    numThreads = re.compile(r'\d+')
    files = []

    for filename in names: 
        if results_files.search(filename) != None:
            files.append(filename)

    computingData = pd.read_csv(files[0])
    nthr = int(numThreads.search(files[0]).group())

    computingData['nthreads'] = [nthr] * len(computingData)

    for f in files[1:]:

        computingDataTmp = pd.read_csv(f)
        nthr = int(numThreads.search(f).group())

        computingDataTmp['nthreads'] = [nthr] * len(computingDataTmp)
        computingData = pd.concat([computingData, computingDataTmp])


    realColumnNames = []
    for colnames in computingData.columns:
        realColumnNames.append(colnames.strip(' '))

    computingData.columns = realColumnNames

    computingData.sort_values(by=['nthreads','size'], inplace = True, ascending = True)

    return computingData



print(createDataframe())



