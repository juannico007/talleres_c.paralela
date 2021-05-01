#!/bin/bash
#
#SBATCH -p dev 		# partition (queue)
#SBATCH -N 1 			# number of nodes
#SBATCH -n 16 			# number of cores
#SBATCH -t 0-08:30 		# time (D-HH:MM)
#SBATCH -o slurm.%N.%j.out 	# STDOUT
#SBATCH -e slurm.%N.%j.err 	# STDERR


mpiexec -np 8 reconstruct_par_v2 edge4896x3264.pgm 8
