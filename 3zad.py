import math
from typing import List, Tuple

def coffee(Tk: float, Tsr: float, r: float, time: int) -> List[float]: # высчитывает температуру кофе со временем
    temperatures = [] # вектор для температуры
    for i in range(1, time+1):
        t = Tsr + (Tk - Tsr) * math.exp(-r * i) # вычисление по закону теплопроводности Ньютона
        temperatures.append(t)
    return temperatures

def aprox(x: List[float], y: List[float]) -> Tuple[float, float]: # значение аппроксимирующей прямой
    sumx = sum(x) # сумма всех х
    sumy = sum(y) # сумма всех у
    xy = sum([a*b for a, b in zip(x, y)]) # сумма произведения всех х на у
    xx = sum([a**2 for a in x]) # сумма всех х в квадрате
    n = len(x)
    a = (n * xy - sumx * sumy) / (n * xx - sumx**2) # пара значений аппроксимирующей прямой
    b = (sumy - a * sumx) / n
    return a, b

def korrel(x: List[float], y: List[float]) -> float: # коэффициент корреляции
    xsr = sum(x) / len(x) # среднее значение х
    ysr = sum(y) / len(y) # среднее значение у
    sumxy = sum([(a - xsr) * (b - ysr) for a, b in zip(x, y)]) # сумма произведения разности всех х и х среднего на разность всех у на у среднего
    sumxx = sum([(a - xsr)**2 for a in x]) # сумма квадрата разности всех х и х среднего
    sumyy = sum([(b - ysr)**2 for b in y]) # сумма квадрата разности всех у и у среднего
    return sumxy / math.sqrt(sumxx * sumyy) # подсчёт коэффициента



Tk = 90  # температура кофе
Tsr = 25  # температура окружающей среды
r = 0.005  # коэффициент остывания
time = 60  # время остывания в минутах
temperatures = coffee(Tk, Tsr, r, time)  # заполнение вектора с температурой
times = []  # вектор для времени
print("__________________________")
print("|" + "{:^8}".format("time (x)") + "|" + "{:^16}".format("temperature (y)") + "|")  # шапка таблицы
for i in range(len(temperatures)):
    j = i + 1
    print("|" + "{:^8}".format(str(j)) + "|" + "{:^16}".format(str(temperatures[i])) + "|")  # вывод значений в табличной форме
    times.append(i)  # заполнение вектора со временем
print("Аппроксимирующая прямая: a = ", end="")
approximatingLine = aprox(times, temperatures)  # заполнение пары со значением аппроксимирующей прямой
print(approximatingLine[0], " b = ", approximatingLine[1])
print("Коэффициент корреляции: r = ", korrel(times, temperatures))
