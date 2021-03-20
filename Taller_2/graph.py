import pandas as pd
import os
from math import sqrt
import matplotlib.pyplot as plt

def getSpeedUps(data):

    """
    Función que dado el dataframe de con los datos
    retorna un diccionario de forma {tamaño del problema:lista de speedup por hilo}


    ej: se testeó para 5 tamaños con 12 hilos
    Si se ingresa el dataframe con los datos recolectados, la fución retornará
    un diccionario de 5 llaves con valores de sublistas de 12 elementos, 
    cada uno con los speedUps para las cantidades de hilos
    """

    #obtención del conjunto de índices del dataframe 
    #que contienen ejecuciones de un solo hilo
    serialExec  = data[data["thr"]==1].index
    
    #creación de lista de listas que va a retornar 
    #los speedUps agrupados por test
    speedUps = {}

    for i in range(len(serialExec)):
        sizeOfIter = data.iloc[i]["size"]             #extrae el tamaño del problema en esta iteracion
        localSerialTimeMean = data.iloc[i]["mean"]    #extrae la media de esa iter serial
        localSpeedUps = []          #lista local para ir almacenando los cálculos de speedUps

        for nextItem in range(i, len(data), len(serialExec)):
            #obtención del tiempo de ejecución medio en paralelo
            parallelExecTime = data.iloc[nextItem]["mean"]
            #calculo del speedUp
            speedUp = localSerialTimeMean/parallelExecTime
            #guardado del speedUp en lista local 
            localSpeedUps.append(speedUp)
            
        speedUps[sizeOfIter] = localSpeedUps  #guardado del paquete de speedUps en la variable 
                                        #de retorno "speedUps"
    return speedUps


def mean(data):
    #INPUT: Una lista de valores
    #OUTPUT: promedio de estos valores
    
    addition = 0

    for i in data: 
        addition += i

    return addition/len(data)

def means_dict(data):
    """
    Funcion que dado un diccionario de {llave:lista de valores}
    retorna un diccionario con las medias de las listas de cada llave
    """
    means = {}
    
    for i in data:
        means[i] = mean(data[i])
        
    return means

def stdDeviation(data):
    #INPUT: Una lista de valores
    #OUTPUT: Desviacion estandar de estos valores
    
    average = mean(data)
    variance = 0

    for i in data:
        variance += (i - average)**2
    
    variance /= len(data)

    return  sqrt(variance)

def stdDeviation_dict(data):
    """
    Funcion que dado un diccionario de {llave:lista de valores}
    retorna un diccionario con las desviaciones estandar de las listas de cada llave
    """
    stdDevs = {}
    
    for i in data:
        stdDevs[i] = stdDeviation(data[i])
        
    return stdDevs


def getThreadData(data):
    """
    Función que dado el dataframe de con los datos
    retorna un diccionario de forma {numero de hilos:lista de [tamaño, media, desviacion estandar]}
    Para graficar despues
    """
    
    data = {}          #Lista de listas con las medias de tiempo de cada hilo
    
    for i in range(len(data)):
        data[i] = data.get(i, []).append((data.iloc[i]["size"], data.iloc[i]["mean"], data.iloc[i]["std dev"]))
        
    return data

def graphSpeedUpM(speedUps, stdDev, n):
    """
    Funcion que dados diccionarios de medias y de desviaciones estandar
    grafica la media de speedups para cada numero de hilos
    Recibe el diccionario de speedups, la de desviaciones estandar y un numero que corresponde al tamaño del arreglo (10^n)
    """
    
    y = [i for i in speedUps[n]]
    x = [i for i in range(2,13)]
    
    fig = plt.figure()
    ax1 = fig.add_subplot()
    ax1.set_ylabel('Speedup')
    ax1.set_xlabel('Numbre of threads')
    ax1.set_title('Speedups for size 10^{0}'.format(n))
    
    speedUpU = [i+stdDev[n] for i in y]
    speedUpL = [i-stdDev[n] for i in y]
    
    ax1.plot(x, y, color='b', lw=2)
    ax1.plot(x, speedUpU, color='b', lw=0.3)
    ax1.plot(x, speedUpL, color='b', lw=0.3)
    ax1.fill_between(x, speedUpU, speedUpL, color = 'lightblue')
    
    #Guarda la imagen en un archivo.jpg que esta en el pdf
    fig.savefig('Speedups for size 10^{0}'.format(n))
    
def graphThreadMean(data, n):
    """
    Funcion que dada un diccionario de datos de hilos de forma {hilos: [(tamaño, media, desviacion  estandar)]}, 
    Grafica la media de tiempo de ejecucion para varios tamaños del problema
    Recibe el diccionario de datos y el numero de hilos a graficar
    """
    x = [data[n][i][0] for i in range(len(data[n]))]
    y = [data[n][i][1] for i in range(len(data[n]))]
    fig = plt.figure()
    ax1 = fig.add_subplot()
    ax1.set_ylabel('Mean (s)')
    ax1.set_xlabel('Size of arrays (10^x)')
    ax1.set_title('Mean of execution time for {0} thread'.format(n + 1))
    
    meanThreadP = [data[n][i][1] + data[n][i][2] for i in range(len(data[n]))]
    meanThreadL = [data[n][i][1] - data[n][i][2] for i in range(len(data[n]))]
    
    ax1.plot(x, y, color='b', lw=2)
    ax1.plot(x, meanThreadP, color='b', lw=0.3)
    ax1.plot(x, meanThreadL, color='b', lw=0.3)
    ax1.fill_between(x, meanThreadP, meanThreadL, color = 'lightblue')
    plt.ylim([0,300])
    #Guarda la imagen en un archivo.jpg que esta en el pdf
    fig.savefig('Mean of execution time for {0} thread'.format(n + 1))




#USO DE TODAS LAS FUNCIONES    

#Dataframe con estructura: mean, std, reps, sz, nthr
#Ordenado por el numero de hilos
speedUps = getSpeedUps(df)

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


#Grafica la media de los speedups para cada tamaño del arreglo
for i in range(5):
    graphSpeedUpM(speedUps, speedUpsStdDev, i)

#Grafica la media de tiempo de ejecucion para cada numero de hilos
for i in range(12):
    graphThreadMean(meanThreads, stdThreads, i)
