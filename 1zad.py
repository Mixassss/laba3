import numpy as np
import math

def pudge(start, end, step):
    for x in np.arange(start, end+step, step):
        if -10 <= x <= -6:
            result = round((-1*(math.sqrt(4-(math.pow(x+8, 2))))+2)*100) / 100
            print(x, "\t", result)
        elif -6 < x <= -4:
            result = 2
            print(x, "\t", result)
        elif -4 < x <= 2:
            result = -0.5 * x
            if result == -0:
                result = abs(result)
            print(x, "\t", result)
        elif x > 2:
            result = x - 3
            print(x, "\t", result)


xstart = int(input("Введите начальный x: "))
xend = int(input("Введите конечный x: "))
step = float(input("Введите шаг: "))
print("X\tY")
pudge(xstart, xend, step)
