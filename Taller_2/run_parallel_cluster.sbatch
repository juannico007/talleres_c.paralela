#!/bin/bash
#
#SBATCH -p gpu 		# partition (queue)
#SBATCH -N 1 			# number of nodes
#SBATCH -n 16 			# number of cores
#SBATCH -t 0-08:30 		# time (D-HH:MM)
#SBATCH -o slurm.%N.%j.out 	# STDOUT
#SBATCH -e slurm.%N.%j.err 	# STDERR


for ((thrs=1; thrs<=16; thrs++))
do
	export OMP_NUM_THREADS=$thrs
	./parallel 100
done





