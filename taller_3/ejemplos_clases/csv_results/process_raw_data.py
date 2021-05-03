import pandas as pd
import os

#lectura de todos los archivos en el directorio y obviado de
#el primer archivo mostrado, el cual es el nombre de este script
csvs = os.listdir(".")[1:]
csvs.remove("resultados_pasados")       #borrado de carpeta innecesaria de la lista
csvs.remove("processed_results.csv")    #borrado del archivo de salida de la lista

print(csvs)

df = pd.read_csv(csvs[0], header=None)  #lectura del dataframe inicial
print(df.head())

#lectura de los demás dataframes y concatenado de estos

for csv in csvs[1:]:
    
    dflocal = pd.read_csv(csv, header=None)
    #print(df.head())

    df = pd.concat([df, dflocal], ignore_index=True)

#renombrado de las columnas por comodidad
df.rename(columns = {0: "time",1: "nreps", 2:"size", 3:"nproc"}, inplace = True)

#se hace el agrupado de los datos en el dataframe
groups = df.groupby(["size", "nreps", "nproc"])


#almacena todos los datos que se van a meter al dataframe
input_data = []

for groupname, frame in groups:
    localdata = []

    print(groupname)
    localdata.append(frame["time"].mean())
    localdata.append(frame["time"].std())
    localdata.append(groupname[1])
    localdata.append(groupname[0])
    localdata.append(groupname[2])
    
    input_data.append(localdata)


#dataframe para guardar los resultados finales
processed_data = pd.DataFrame(input_data, columns = ["Mean time", "std deviation", "reps", "size", "nprocesses"])
processed_data.sort_values(by=["reps", "size"], ascending=True)


print(df.head())
processed_data.to_csv("processed_results.csv", index=False)



