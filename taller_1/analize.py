import pandas as pd
from math import sqrt
import matplotlib.pyplot as plt

def getSpeedUp(data, nthreads):

    """
    Función que dado el dataframe de con los datos
    y dado el número de hilos máximo hasta los que se hicieron los
    cálculos, retorna una lista de sublistas que contienen los speedUps
    para cada subtesteo de tamaño de matriz fijo


    ej: se testeó 5 veces con 12 hilos, y un tamaño de matriz que 
    aumentaba en cada test individual en un factor de 10; si se ingresa
    el dataframe con los datos recolectados, la fución retornará
    una lista de 5 sublistas, cada una con los speedUps para las cantidades de hilos
    """

    #obtención del conjunto de índices del dataframe 
    #que contienen ejecuciones de un solo hilo
    serialExec  = data[data["thr"]==1].index
    
    #creación de lista de listas que va a retornar 
    #los speedUps agrupados por test
    speedUps = []

    for i in range(0, len(serialExec)):

        localSerialExecIndx = serialExec[i]     #toma el índice de la iteración serial
        localSerialTimeMean = data.iloc[localSerialExecIndx]["mean"]    #extrae la media de esa iter serial
        localSpeedUps = []          #lista local para ir almacenando los cálculos de speedUps

        for nextItem in range(1, nthreads):

            #obtención del tiempo de ejecución medio en paralelo
            parallelExecTime = data.iloc[localSerialExecIndx + nextItem]["mean"]
            #calculo del speedUp
            speedUp = localSerialTimeMean/parallelExecTime
            #guardado del speedUp en lista local 
            localSpeedUps.append(speedUp)

        speedUps.append(localSpeedUps)  #guardado del paquete de speedUps en la variable 
                                        #de retorno "speedUps"

    return speedUps

def mean(data):
    #INPUT: Una lista de valores
    #OUTPUT: promedio de estos valores
    
    addition = 0

    for i in data: 
        addition += i

    return addition/len(data)


def stdDeviation(data):

    average = mean(data)
    variance = 0

    for i in data:
        variance += (i - average)**2
    
    variance /= len(data)

    return  sqrt(variance)

def getMeanThread(data, nthreads):
    #Funcion que dado el dataframe retorna una lista de listas con las medias de cada numero de hilos
    #Necesita el numero de hilos ocn los que se trabajo
    
    means = [[] for i in range(nthreads)]          #Lista de listas con las medias de tiempo de cada hilo
    
    for i in range(len(data)):
        means[i % 12].append(data.iloc[i]["mean"])
        
    return means

def getStdThread(data, nthreads):
    #Funcion que dado el dataframe retorna una lista de listas con las medias de cada numero de hilos
    #Necesita el numero de hilos ocn los que se trabajo
    
    devs = [[] for i in range(nthreads)]          #Lista de listas con las medias de tiempo de cada hilo
    
    for i in range(len(data)):
        devs[i % 12].append(data.iloc[i]["std dev"])
        
    return devs

#USO DE TODAS LAS FUNCIONES

df = pd.read_csv("time_data.csv")

speedUps = getSpeedUp(df, 12)
print("speedups: \n", speedUps)
print()

speedUpsMean = list(map(mean, speedUps))
print("speedups mean:\n", speedUpsMean)
print()

speedUpsStdDev = list(map(stdDeviation, speedUps))
print("speedups standar desviation\n", speedUpsStdDev)
print()

meanThreads = getMeanThread(df, 12)
print("Mean per thread:\n", meanThreads)
print()

stdThreads = getStdThread(df, 12)
print("Standar desviation per thread:\n", stdThreads)

x = [4, 5, 6, 7, 8]
speedUpsMeanP = [speedUpsMean[i] + speedUpsStdDev[i] for i in range(len(speedUpsMean))]
speedUpsMeanL = [speedUpsMean[i] - speedUpsStdDev[i] for i in range(len(speedUpsMean))]


speedUpsG = plt.figure()
ax1 = speedUpsG.add_subplot()
ax1.set_ylabel('Speedups mean')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of speedups in matrix multiplication')

ax1.plot(x, speedUpsMean, color='b', lw=2)
ax1.plot(x, speedUpsMeanP, color='b', lw=0.3)
ax1.plot(x, speedUpsMeanL, color='b', lw=0.3)
ax1.fill_between(x, speedUpsMeanP, speedUpsMeanL, color = 'lightblue')



#1 Thread 
meanThread1 = plt.figure()
ax1 = meanThread1.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 1 thread')

meanThreadP = [meanThreads[0][i] + stdThreads[0][i] for i in range(len(meanThreads[0]))]
meanThreadL = [meanThreads[0][i] - stdThreads[0][i] for i in range(len(meanThreads[0]))]

ax1.plot(x, meanThreads[0], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#2 Threads
meanThread2 = plt.figure()
ax1 = meanThread2.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 2 threads')

meanThreadP = [meanThreads[1][i] + stdThreads[1][i] for i in range(len(meanThreads[1]))]
meanThreadL = [meanThreads[1][i] - stdThreads[1][i] for i in range(len(meanThreads[1]))]

ax1.plot(x, meanThreads[1], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#3 Threads
meanThread3 = plt.figure()
ax1 = meanThread3.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 3 threads')

meanThreadP = [meanThreads[2][i] + stdThreads[2][i] for i in range(len(meanThreads[2]))]
meanThreadL = [meanThreads[2][i] - stdThreads[2][i] for i in range(len(meanThreads[2]))]

ax1.plot(x, meanThreads[2], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#4 Threads
meanThread4 = plt.figure()
ax1 = meanThread4.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 4 threads')

meanThreadP = [meanThreads[3][i] + stdThreads[3][i] for i in range(len(meanThreads[3]))]
meanThreadL = [meanThreads[3][i] - stdThreads[3][i] for i in range(len(meanThreads[3]))]

ax1.plot(x, meanThreads[3], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#5 Threads
meanThread5 = plt.figure()
ax1 = meanThread5.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 5 threads')

meanThreadP = [meanThreads[4][i] + stdThreads[4][i] for i in range(len(meanThreads[4]))]
meanThreadL = [meanThreads[4][i] - stdThreads[4][i] for i in range(len(meanThreads[4]))]

ax1.plot(x, meanThreads[4], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#6 Threads
meanThread6 = plt.figure()
ax1 = meanThread6.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 6 threads')

meanThreadP = [meanThreads[5][i] + stdThreads[5][i] for i in range(len(meanThreads[5]))]
meanThreadL = [meanThreads[5][i] - stdThreads[5][i] for i in range(len(meanThreads[5]))]

ax1.plot(x, meanThreads[5], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#7 Threads
meanThread7 = plt.figure()
ax1 = meanThread7.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 7 threads')

meanThreadP = [meanThreads[6][i] + stdThreads[6][i] for i in range(len(meanThreads[6]))]
meanThreadL = [meanThreads[6][i] - stdThreads[6][i] for i in range(len(meanThreads[6]))]

ax1.plot(x, meanThreads[6], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#8 Threads
meanThread8 = plt.figure()
ax1 = meanThread8.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 8 threads')

meanThreadP = [meanThreads[7][i] + stdThreads[7][i] for i in range(len(meanThreads[7]))]
meanThreadL = [meanThreads[7][i] - stdThreads[7][i] for i in range(len(meanThreads[7]))]

ax1.plot(x, meanThreads[7], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#9 Threads
meanThread9 = plt.figure()
ax1 = meanThread9.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 9 threads')

meanThreadP = [meanThreads[8][i] + stdThreads[8][i] for i in range(len(meanThreads[8]))]
meanThreadL = [meanThreads[8][i] - stdThreads[8][i] for i in range(len(meanThreads[8]))]

ax1.plot(x, meanThreads[8], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#10 Threads
meanThread1 = plt.figure()
ax1 = meanThread1.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 10 threads')

meanThreadP = [meanThreads[9][i] + stdThreads[9][i] for i in range(len(meanThreads[9]))]
meanThreadL = [meanThreads[9][i] - stdThreads[9][i] for i in range(len(meanThreads[9]))]

ax1.plot(x, meanThreads[9], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#11 Threads
meanThread1 = plt.figure()
ax1 = meanThread1.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 11 threads')

meanThreadP = [meanThreads[10][i] + stdThreads[10][i] for i in range(len(meanThreads[10]))]
meanThreadL = [meanThreads[10][i] - stdThreads[10][i] for i in range(len(meanThreads[10]))]

ax1.plot(x, meanThreads[10], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')

#12 Threads
meanThread1 = plt.figure()
ax1 = meanThread1.add_subplot()
ax1.set_ylabel('Mean (s)')
ax1.set_xlabel('Size of arrays (10^x)')
ax1.set_title('Mean of execution time for 12 threads')

meanThreadP = [meanThreads[11][i] + stdThreads[11][i] for i in range(len(meanThreads[11]))]
meanThreadL = [meanThreads[11][i] - stdThreads[11][i] for i in range(len(meanThreads[11]))]

ax1.plot(x, meanThreads[11], color='b', lw=2)
ax1.plot(x, meanThreadP, color='b', lw=0.3)
ax1.plot(x, meanThreadL, color='b', lw=0.3)
ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')


plt.show()