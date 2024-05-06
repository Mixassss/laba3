import random
import math

def Eratos(num): # решето Эратосфена
    numbersToNum = [i for i in range(num)]
    Prostie = []
    
    for i in range(2, num):
        if numbersToNum[i] != 0:
            for j in range(i + numbersToNum[i], num, numbersToNum[i]):
                numbersToNum[j] = 0
    
    for i in range(num):
        if numbersToNum[i] != 0 and numbersToNum[i] != 1:
            Prostie.append(numbersToNum[i])
    
    return Prostie

def Moded(number, m):
    result = 1
    for i in range(m):
        result *= number
        result %= (m + 1)
    
    return result

def Generator(numberProst, n, number, dividers, R): # Генератор
    m = (n - 1) // R
    i = 0
    while m > 1:
        if m % numberProst[i] == 0:
            dividers.append(numberProst[i])
            m //= numberProst[i]
        else:
            i += 1
    t = 5
    for j in range(t):
        number.append(random.random() % n)
    for j in number:
        if (Moded(j, n - 1) % n) != 1:
            return 0
    return 1

def Miller(numberProst, n): # тест Миллера
    dividers = []
    number = []
    test = Generator(numberProst, n, number, dividers, 2)
    if test == 0:
        return 0
    k = 0
    for j in dividers:
        for z in number:
            if (Moded(z, (n - 1) // j) % n) != 1:
                k += 1
                break
    if k == 0:
        return 0
    return 1

def Poli(numberProst, n): # тест Поклингтона
    k = 0
    dividers = []
    number = []
    R = 4
    if (n // 8) != 0:
        R = random.randint(0, n // 8) * 2
        if R == 0:
            R = 4
    test = Generator(numberProst, n, number, dividers, R)
    if test == 0:
        return 0
    for z in number:
        for j in dividers:
            if (Moded(z, (n - 1) // j) % n) == 1:
                k += 1
                break
    if k == 0:
        return 1
    return 0

def power(a, b): # степень
    s = 1
    for i in range(b):
        s = s * a 
    return s

def powerMod(a, b, m): # a^x mod p
    s = 1
    for i in range(b):
        s = s * a
        s = s % m
    return s

def GOST(t, q): # ГОСТ Р 34.10 - 94.
    f = False
    p = 0
    while True:
        N = power(2, t - 1) // q
        if N % 2 == 1:
            N += 1
        u = 0
        while True:
            p = (N + u) * q + 1
            if power(2, t) < p:
                break
            if (power(2, p - 1) % p == 1) and (power(2, N + u) % p != 1):
                f = True
                break
            u = u + 2
        if f:
            return p
        
def MillerRabin(number, k): # Миллер-Рабин
    if number == 2 or number == 3:
        return 1
    if number < 2 or number % 2 == 0:
        return 0
    
    d = number - 1
    s = 0
    y = 0
    
    while d % 2 == 0:
        d //= 2
        s += 1
    
    for i in range(k):
        a = random.randint(2, number-4)
        x = powerMod(a, d, number)
        
        for j in range(s):
            y = (x * x) % number
            if y == 1 and x != 1 and x != (number - 1):
                return 0
            x = y
        
        if y != 1:
            return 0
    
    return 1

num = 500
Prostie = Eratos(num)
print("Простые числа до", num, ": ")
for i in Prostie:
    print("{:4}".format(i), end="")
print()

t = 5
q = 7
if q < power(2, t // 2 + 1):
    number = GOST(t, q)
    print(number)

ReallyProstie = []
BadOnes = []
MissedOnes = 0
TotalNums = 0
while len(ReallyProstie) < 10:
    test = random.randint(2, 500-4)
    if Miller(Prostie, test) and Poli(Prostie, test):
        ReallyProstie.append(test)
        BadOnes.append(MissedOnes)
        MissedOnes = 0
    else:
        MissedOnes += MillerRabin(test, 10)
    TotalNums += 1

print("Счетчик простых отвергнутых чисел:", end=" ")
for i in BadOnes:
    print(i, end=" ")
MissedOnes = 0
print()
print("Пройдено чисел:", TotalNums)
print("10 Получившихся чисел:")
for i in ReallyProstie:
    print("{:5}".format(i), end="")
    MissedOnes = MillerRabin(i, 10)
    if MissedOnes == 1:
        print(" +")
    else:
        print(" -")
