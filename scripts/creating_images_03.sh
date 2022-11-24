#!/bin/bash

r_values="568 576 584 592 600 608 616 624 632 640 648 656 664 672 680 688 696 704 712 720"

if [ ! -z $1 ]; then
	r_values=$1
fi

mkdir -p data

echo "Creating images..."

for r in $r_values; do
	echo -n -e "r=$r\r"
	r_with_zeros=$(printf "%03d" $r)
	./project1 -s scenes/scene_10 -ry "$r" -o ../../data/"$r_with_zeros".png
done


