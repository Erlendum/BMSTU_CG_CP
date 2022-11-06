#!/bin/bash

files=$(ls ./prepdata/)

mkdir -p postproc
echo "Postproc..."
rm -f ./postproc/_data.txt

for file in $files; do
	echo -n -e "r="$file" \r"
	python3 scripts/threads/postproc_error_plot.py < ./prepdata/$file >> ./postproc/"data_${file:1:-9}".txt "$file"
done
