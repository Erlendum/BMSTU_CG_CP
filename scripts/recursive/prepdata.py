import math

numbers = []
try:
    while True:
        numbers.append(float(input()))

except EOFError:
    mean = sum(numbers) / len(numbers)
    var = sum((l-mean)**2 for l in numbers) / len(numbers)
    std = math.sqrt(var)
    threshold = 3
    outlier = []
    for i in numbers:
        z = (i - mean) / std
        if z > threshold:
            outlier.append(i)
            numbers.remove(i)
    print('outliers in dataset are' , outlier) 

    print(mean, min(numbers), max(numbers))
