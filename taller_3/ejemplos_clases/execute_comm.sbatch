#!/bin/bash
#
#SBATCH -p gpu 		# partition (queue)
#SBATCH -N 1 			# number of nodes
#SBATCH -n 16 			# number of cores
#SBATCH -t 0-08:30 		# time (D-HH:MM)
#SBATCH -o slurm.%N.%j.out 	# STDOUT
#SBATCH -e slurm.%N.%j.err 	# STDERR

declare -a StringArray=("edge192x128.pgm" "edge256x192.pgm" "edge512x384.pgm" "edge768x768.pgm")

for filename in "${StringArray[@]}"
do
	for ((nprocess = 2; nprocess <= 16; nprocess*=2))
	do
		for((niters = 10; niters <=100000; niters*=10))
		do
			file="resultados_${filename:0:-4}_${nprocess}.csv"
			mpiexec -np $nprocess reconstruct_par $filename $niters $nprocess >> $file
		done	
	done
done

