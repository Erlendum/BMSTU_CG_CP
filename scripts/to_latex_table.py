import os, glob
import math

def append_to_dictionary(dictionary, key, value):
    if key in dictionary.keys():
        dictionary[key].append(value)
    else:
        a = list()
        a.append(value)
        dictionary[key] = a 

a = []
path = './postproc'
filenames = []
for filename in glob.glob(os.path.join(path, '*.txt')):
   filenames.append(filename)
filenames.sort()
for filename in filenames:
    with open(os.path.join(os.getcwd(), filename), 'r') as f:
        a.append(f.readlines())

max_len = 0
max_len_index = 0
for i in range(len(a)):
    if len(a[i]) > max_len:
        max_len = len(a[i])
        max_len_index = i

for i in range(len(a)):
    if len(a[i]) < max_len:
        for j in range(len(a[i]), max_len):
            a[i].append(a[max_len_index][j].split()[0] + ' NaN')

m = []
for f in a:
    for k in f:
        m.append(k.split())

for i in range(len(m)):
    m[i][0] = m[i][0].lstrip('0')

dictionary = dict()

for l in m:
    append_to_dictionary(dictionary, l[0], l[1])

for key in dictionary.keys():
    print(key, end=' & ')
    for el in dictionary[key]:
        if dictionary[key].index(el) == len(dictionary[key]) - 1:
            print(el, end=' ')
        else:
            print(el, end=' & ')
    print('\\\\ \\hline')
