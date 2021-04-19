for ((thrs=1; thrs<=12; thrs++))
do
	export OMP_NUM_THREADS=$thrs
	./parallel 100
done





