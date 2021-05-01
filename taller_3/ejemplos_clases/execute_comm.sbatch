#!/bin/bash
#
#SBATCH -p gpu 		# partition (queue)
#SBATCH -N 2 			# number of nodes
#SBATCH -n 16 			# number of cores
#SBATCH -t 0-08:30 		# time (D-HH:MM)
#SBATCH -o slurm.%N.%j.out 	# STDOUT
#SBATCH -e slurm.%N.%j.err 	# STDERR


for ((proc=1; proc<=32; proc*=2))
do
	mpiexec -np proc reconstruccion edge192x128.pgm proc
done
