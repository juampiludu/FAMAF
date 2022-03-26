# Ejercicio 9

def horn(coefs, x):
    out = coefs[0]
    for i in range(1, len(coefs)):
        if i == len(coefs)-1:
            out+=coefs[i]
        else:
            out+=coefs[i]*x
    return out

p = horn([10,8,-6,2,-5,4,2],1)
print(p)


# Ejercicio 10

def sonReciprocos(x,y):
    return x*y == 1

import random
for _ in range(100):
    x = 1 + random.random()
    y = 1/x
    if not sonReciprocos(x,y):
        print(x)


# Ejercicio 11

from math import sqrt

def f(x):
    res = sqrt(x**2+1)-1
    return res

def g(x):
    res = (x**2)/(sqrt(x**2+1)+1)
    return res

for i in range(20):
    x = 8**-i
    print(f"f(x)={f(x)}, g(x)={g(x)}")