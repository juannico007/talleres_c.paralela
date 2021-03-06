import os
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
        means[i % 12].append(data.iloc[i]["mean"])      #Añade en cada sublista la media de tiempo para cierto tamaño
        
    return means

def getStdThread(data, nthreads):
    #Funcion que dado el dataframe retorna una lista de listas con las medias de cada numero de hilos
    #Necesita el numero de hilos ocn los que se trabajo
    
    devs = [[] for i in range(nthreads)]          #Lista de listas con las deviaciones estandar de tiempo de cada hilo
    
    for i in range(len(data)):
        devs[i % 12].append(data.iloc[i]["std dev"])    #Añade en cada sublista la desviacion estandar para cada tamaño
        
    return devs

def createNeededFolders():

    """
    Crea las carpetas necesarias para guardad las imágenes y archivos
    """
    cwd = os.getcwd()
    folder_name = "Plots"

    path = os.path.join(cwd, folder_name)

    if not os.path.exists(path):
        os.mkdir(path)

   


def graphSpeedUpM(speedUps, stdDev, n):
    #Funcion que dada una lista de listas de speedUps para cada tamaño de arreglo 
    #grafica la media de speedups para cada numero de hilos
    #Recibe la lista de speedups, la de desviaciones estandar y un numero que corresponde al tamaño del arreglo (10^n)
    y = [i for i in speedUps[n]]
    x = [i for i in range(2,13)]
    
    fig = plt.figure()
    ax1 = fig.add_subplot()
    ax1.set_ylabel('Speedup')
    ax1.set_xlabel('Numbre of threads')
    ax1.set_title('Speedups for size 10^{0}'.format(n + 4))
    
    speedUpU = [i+stdDev[n] for i in y]
    speedUpL = [i-stdDev[n] for i in y]
    
    ax1.plot(x, y, color='b', lw=2)
    ax1.plot(x, speedUpU, color='b', lw=0.3)
    ax1.plot(x, speedUpL, color='b', lw=0.3)
    ax1.fill_between(x, speedUpU, speedUpL, color = 'lightblue')
    
    #Guarda la imagen en un archivo.jpg que esta en el pdf
    fig.savefig('./Plots/Speedups for size 10^{0}'.format(n + 4))
    
def graphThreadMean(means, stdDev, n):
    #Funcion que dada una lista de medias por hilos, 
    #Grafica la media de tiempo de ejecucion para varios tamaños de la matriz
    #Recibe la lista de medias por hilo, una lista de desviaciones estandar por hilo y el numero de hilos a graficar
    x = [4, 5, 6, 7, 8]
    fig = plt.figure()
    ax1 = fig.add_subplot()
    ax1.set_ylabel('Mean (s)')
    ax1.set_xlabel('Size of arrays (10^x)')
    ax1.set_title('Mean of execution time for {0} thread'.format(n + 1))
    
    meanThreadP = [means[n][i] + stdDev[n][i] for i in range(len(means[n]))]
    meanThreadL = [means[n][i] - stdDev[n][i] for i in range(len(means[n]))]
    
    ax1.plot(x, means[n], color='b', lw=2)
    ax1.plot(x, meanThreadP, color='b', lw=0.3)
    ax1.plot(x, meanThreadL, color='b', lw=0.3)
    ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')
    plt.ylim([0,300])
    #Guarda la imagen en un archivo.jpg que esta en el pdf
    fig.savefig('./Plots/Mean of execution time for {0} thread'.format(n + 1))


#USO DE TODAS LAS FUNCIONES

df = pd.read_csv("./data/time_data.csv")

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


createNeededFolders()

#Grafica la media de los speedups para cada tamaño del arreglo
for i in range(5):
    graphSpeedUpM(speedUps, speedUpsStdDev, i)

#Grafica la media de tiempo de ejecucion para cada numero de hilos
for i in range(12):
    graphThreadMean(meanThreads, stdThreads, i)


