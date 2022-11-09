import numpy as np

x_limits = (-0.5, 0.5)
y_limits = (-0.5, 0.5)
z_limits = (-0.5, 0.5)

z_values = np.linspace(x_limits[0], x_limits[1], 10)

for z in z_values:
    if z != z_limits[0] and z != z_limits[1]:
        print('v', x_limits[0], y_limits[0], z)
        print('v', x_limits[1], y_limits[0], z)
        print('v', x_limits[0], y_limits[1], z)
        print('v', x_limits[1], y_limits[1], z)

k = 0
for _ in range(len(z_values) - 2):
    print('f', str(1 * k + 1) + '//', str(1 * k + 2) + '//', str(1 * k + 3) + '//')
    print('f', str(1 * k + 3) + '//', str(1 * k + 2) + '//', str(1 * k + 4) + '//')
    k += 4

print(k / 4)