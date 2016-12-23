#!/bin/bash

for c in `seq 1 8`; do
	for n in `seq 500 500 8000`; do
		# Resultats molt erratics quan es buiden caches
		# sync && echo 3 > /proc/sys/vm/drop_caches
		echo $c $n
		time ./main.exe -p -f 2008.csv -c $c -n $n -b 8192
	done
done
