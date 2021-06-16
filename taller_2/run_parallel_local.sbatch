for ((thrs=1; thrs<=12; thrs++))
do
	export OMP_NUM_THREADS=$thrs
	./c++Files/parallel 100
done





