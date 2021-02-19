import pandas as pd

def getSpeedUp(data, nthreads):

"""
Función que dado el dataframe de con los datos
y dado el número de hilos máximo hasta los que se hicieron los
cálculos, retorna una lista de sublistas que contienen los speedUps
para cada subtesteo de tamaño de matriz fijo


ej: se testeó 3 veces con 12 hilos, y un tamaño de matriz que 
aumentaba en cada test individual en un factor de 10; si se ingresa
el dataframe con los datos recolectados, la fución retornará
una lista de 3 sublistas, cada una con los speedUps para las cantidades de hilos
"""

    #obtención del conjunto de índices del dataframe 
    #que contienen ejecuciones de un solo hilo
    serialExcec  = data[data["thr"]==1].index

    #creación de lista de listas que va a retornar 
    #los speedUps agrupados por test
    speedUps = []

    for i in range(0, len(serialExcec)):

        localSerialExecIndx = serialExcec[i]     #toma el índice de la iteración serial
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


df = pd.read_csv("time_data.csv")




