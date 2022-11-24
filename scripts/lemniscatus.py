import numpy as np

def f(x):
    return ((9 * x ** 2 - x ** 4) / (x ** 2 + 9)) ** 0.5

x = np.linspace(0, 3, 20)
z = [f(el) for el in x]



mx = [el for el in x]
mz = [el for el in z]

mx += mx[::-1]
mz += [-el for el in mz[::-1]]

mx += [-el for el in mx]
mz += [el for el in mz]

# for el in mx:
#     print("\""+ str(el) + "\"", end=' ')

for el in mz:
    print("\""+ str(-el) + "\"", end=' ')

# i = 0
# k = 360
# while i < len(mx):
#     print(k, end=' ')
#     k += 2
#     i += 1