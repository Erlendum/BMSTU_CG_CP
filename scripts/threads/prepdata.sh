#!/bin/bash

files=$(ls ./data/)

mkdir -p prepdata
echo "Prepdata..."

for file in $files; do
	echo -n -e "r="$file" \r"
	python3 scripts/threads/prepdata.py < ./data/$file > ./prepdata/$file
done
