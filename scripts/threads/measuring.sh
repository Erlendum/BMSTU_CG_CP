#!/bin/bash

t_values="8"
s_values="128 256 352 448 512 640"
count=5

if [ ! -z $1 ]; then
	t_values=$1
fi
if [ ! -z $2 ]; then
	s_values=$2
fi
if [ ! -z $3 ]; then
	count=$3
fi

mkdir -p data

echo "Measuring..."

for cur in $(seq "$count"); do
	for t in $t_values; do
        for s in $s_values; do
		    echo -n -e "$cur/$count "t=$t"  "s=$s" \r"
		    t_with_zeros=$(printf "%03d" $t)
            s_with_zeros=$(printf "%03d" $s)
		    project/project -s scenes/scene_05 -size "$s" -t "$t" >> ./data/t"$t_with_zeros"_s"$s_with_zeros".txt
        done
	done
done
