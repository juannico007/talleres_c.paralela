# Taller 1 Computación Paralela, concurrente y distribuída en C++
----

### Objetivo: Paralelizar un producto de matrices usando thread de C++

#### Organización del taller:

Todo el archivo principal es invocado en ***'main\_p.cpp'*** este se compone de:
***'matrix\_one\_p.cpp'*** *(implementa la clase que hace esta operación de
producto matricial)*, ***'matrix\_one.hpp'*** *(Declara la estructura de la clase)*, y de ***'helper.cpp'***, ***'helper.hpp'***, donde
se define y se implementan funciones para calcular la media del tiempo de ejecución y su desviación estándar.

#### Ejecutar el script: 

Para ejecutar el código corra las siguientes líneas: 

* En caso de que desee evaluar el modelo para sus propios datos: 

	* Borrar los resultados existentes y crear archivos necesarios:

			rm ./data/* -rf
			rm ./Plots/* -rf

			touch ./data/time_data.csv 

			cd ./c++Files 
			make main_p 

	* Ejecutar el script, guardar los datos y realizar el análsis: 

			cd .. 
			echo 'mean,std dev,reps,size a,size b,thr' >> ./data/time_data.csv
			./c++Files/main_p 100000 30 >> ./data/time_data.csv
			python3 analize.py

* Si desea hacer el análsis para los datos dados: 

			cd ./c++Files 
			make main_p 

			python3 ../analize.py

Las imágenes de los análisis se pueden ver dentro de la carpeta ***'Plots'***.

Tenga en cuenta que el ejecutable **'main\_p'** recibe 2 argumentos, el tamaño de las matrices 
sobre las cuales se va a operar, y el número de veces que se quiere repetir la operación para calcular
desviaciones estándar y medias de tiempo de ejecución.




