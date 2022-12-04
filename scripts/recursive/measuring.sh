#!/bin/bash

r_values="0 1 2 3 4 5 6 7 8 9 10"
count=10

if [ ! -z $1 ]; then
	r_values=$1
fi
if [ ! -z $2 ]; then
	count=$2
fi

mkdir -p data

echo "Measuring..."

for cur in $(seq "$count"); do
	for r in $r_values; do
		echo -n -e "$cur/$count "r=$r" \r"
		r_with_zeros=$(printf "%02d" $r)
		project/project -s scenes/scene_05 -r "$r" >> ./data/"$r_with_zeros".txt
	done
done
