def transporte(pasajeros):
    pasajeros_aux = pasajeros.copy()
    r = 0
    while len(pasajeros_aux) > 0:
        count = 0
        pasajero = pasajeros_aux[0]
        for i in range(1,len(pasajeros_aux)):
            if pasajero.get('b') <= pasajeros_aux[i].get('s'):
                count += 1
        r = max(count, r)
        pasajeros_aux.remove(pasajero)
    return r


p1 = {'s':1,'b':2} # 3
p2 = {'s':1,'b':5} # 2
p3 = {'s':3,'b':5} # 3
p4 = {'s':1,'b':6} # 1
p5 = {'s':5,'b':6} # 3
p6 = {'s':3,'b':4} # 4
p7 = {'s':2,'b':4} # 3

pasajeros = [p1,p2,p3,p4,p5,p6,p7]

print(transporte(pasajeros))