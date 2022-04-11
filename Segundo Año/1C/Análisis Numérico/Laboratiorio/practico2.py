from math import tan
import sys

#ej1

def rbisec(funcion, intervalo : list, error, iteraciones : int) -> tuple:
    puntos_medios : list = []
    valores_funcionales : list = []

    a = intervalo[0]
    b = intervalo[1]

    fa = funcion(a)
    fb = funcion(b)

    e = b-a

    if fa*fb > 0:
        print("STOP(1)\nError, la funcion no tiene raices en el intervalo dado")
        return puntos_medios, valores_funcionales

    for k in range(iteraciones):
        e = e/2
        punto_medio = a + e
        valor_func_punto_medio = funcion(punto_medio) 

        puntos_medios.append(punto_medio)
        valores_funcionales.append(valor_func_punto_medio)

        print(f"[{k}] - x: {punto_medio}\t\tf(x): {valor_func_punto_medio}")

        if abs(funcion(e)) < error or abs(valor_func_punto_medio) < sys.float_info.epsilon:
            print ("STOP(2)\nError, error lo suficientemente chico\n")
            break

        if fa*valor_func_punto_medio < 0:
            b = punto_medio
            fb = valor_func_punto_medio
        else:
            a = punto_medio
            fa = valor_func_punto_medio
    
    return puntos_medios, valores_funcionales

# ej2

def min_poas(arr):
    return arr.index(min([i for i in arr if i > 0]))

def fun_lab2ej2a(x):
    return 2*x-tan(x)

# hx, hy = rbisec(fun_lab2ej2a, [0.8,1.4], 1e-5, 100)
# mini = min_poas(hy)
# print("\n\n")
# print(f"Respuesta :: iteracion: {mini} - x: {hx[mini]} - f(x): {hy[mini]}")


def fun_lab2ej1b(x):
    return x**2-3

# hx, hy = rbisec(fun_lab2ej1b, [1,2], 1e-5, 100)
# mini = min_poas(hy)
# print("\n\n")
# print(f"Respuesta :: iteracion: {mini} - x: {hx[mini]} - f(x): {hy[mini]}")


# ej3

def rnewton(fun, x0, a, err, mit):
    """
    rnewton aproxima la raíz de una función utilizando el método de Newton.

    fun: toma una funcion que a su vez toma un valor x y un número arbitrario a y devuelve f(x) y fprima(x).
    x0: es un valor inicial que usa la función para empezar a aproximar.
    a: es el número arbitrario que se pasa a la funcion "fun".
    err: es el menor error permitido.
    mit: es la cantidad máxima de iteraciones.
    """
    orig, derivada = fun(x0, a)
    v = orig

    hx = []
    hf = []

    if abs(v) < sys.float_info.epsilon:
        print ("STOP(1)\nEl punto inicial satisface la tolerancia del valor funcional")
        return (hx, hf)

    for k in range(mit):
        if not derivada == 0:
            x1 = x0 - (v/derivada)
            v, _ = fun(x1, a)

            hx.append(x1)
            hf.append(v)

            print(f"[{k}] - x: {x1}\t\tf(x): {v}")

            if abs((x1 - x0)/x1) < err or abs(v) < err:
                print ("STOP(2)\nEl error es demasiado chico")
                break

            x0 = x1

    return hx, hf

# ej4

def fun_lab2ej4(x, a):
    orig = x**3 - a
    derivada = 3*(x**2)
    return orig, derivada


hx, hy = rnewton(fun_lab2ej4, 1.2, 3, 1e-6, 100)
mini = min_poas(hy)
print("\n\n")
print(f"Respuesta :: iteracion: {mini} - x: {hx[mini]} - f(x): {hy[mini]}")