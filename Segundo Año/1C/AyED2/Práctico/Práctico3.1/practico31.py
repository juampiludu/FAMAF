# ej3

def travel(autonomy : int(), towns : list(), distances : list()):
    stops = list()
    fuel = 0
    for i in range(len(distances)):
        if fuel >= distances[i]:
            fuel -= distances[i]
        else:
            fuel = autonomy - distances[i]
            stops.append(towns[i])
    return stops


def ej3():
    towns = ['loc1', 'loc2', 'loc3', 'loc4', 'loc5', 'loc6', 'loc7', 'loc8']
    distances = [90,100,30,80,10,14,5]
    autonomy = 100
    res = travel(autonomy, towns, distances)
    print(res)




# ej4

def rescue_whale(rescue_t : int(), whales : list()):
    whales_aux = whales.copy()
    t_curr = rescue_t
    w = tuple()
    r = list()
    for _ in whales:
        w = min_surv_t_whale(whales_aux)
        if w[1] >= t_curr:
            t_curr += rescue_t
            r.append(w[0])
        whales_aux.remove(w)
    return r

def min_surv_t_whale(whales : list()):
    r = whales[0]
    for i in range(1, len(whales)):
        if whales[i][1] < r[1]:
            r = whales[i]
    return r


def ej4():
    w1 = ('w1', 14)
    w2 = ('w2', 18)
    w3 = ('w3', 13)
    w4 = ('w4', 5)
    w5 = ('w5', 9)
    t = 4
    whales = [w1, w2, w3, w4, w5]
    res = rescue_whale(t, whales)
    print(res)




# ej6

def cook_time(pieces : list()):
    sum_t = 0
    open_count = 0
    pieces_aux = pieces.copy()
    while (len(pieces_aux) > 0):
        curr_min_t = get_min_t(pieces_aux)
        if sum_t == curr_min_t:
            pieces_aux = drop_p(sum_t, pieces_aux)
            open_count += 1
        else:
            sum_t += 1
    return open_count

def drop_p(t_min : int(), pieces : list()) -> list():
    pieces_aux = pieces.copy()
    for i in pieces:
        if t_min == i[0]:
            pieces_aux.remove(i)
    return pieces_aux

def get_min_t(pieces : list()) -> int():
    min = pieces[0][0]
    for i in range(1, len(pieces)):
        min = pieces[i][0] if pieces[i][0] < min else min
    return min


def ej6():
    # facturas        - t_min: 5, t_max: 5
    # criollitos      - t_min: 2, t_max: 3
    # galletas        - t_min: 1, t_max: 1
    # masitas         - t_min: 1, t_max: 2
    # cubanitos       - t_min: 2, t_max: 4
    # magdalenas      - t_min: 3, t_max: 6

    facturas = (5,5)
    criollitos = (2,3)
    galletas = (1,1)
    masitas = (1,2)
    cubanitos = (2,4)
    madalenas = (3,6)

    pieces = [facturas, criollitos, galletas, masitas, cubanitos, madalenas]

    cook = cook_time(pieces)
    print(cook)



# ej7

def save_people(people : list(), ox_t : int(), rescue_t : int()):
    people_aux = people.copy()
    min_ox_p = tuple()
    total_rescue_p = 0
    while len(people_aux) > 0:
        min_ox_p = get_min_ox_p(people_aux)
        ox_t -= rescue_t * min_ox_p
        if ox_t >= 0:
            total_rescue_p += 1
        people_aux.remove(min_ox_p)
    return total_rescue_p

def get_min_ox_p(people : list()):
    p = people[0]
    for i in range(1, len(people)):
        p = people[i] if people[i] < p else p
    return p


def ej7():
    C = 10000 # cantidad de oxigeno

    t = 90 # minutos de rescate por cada persona

    s1 = 35 # oxigeno por minuto
    s2 = 50 # oxigeno por minuto
    s3 = 15 # oxigeno por minuto
    s4 = 20 # oxigeno por minuto
    s5 = 20 # oxigeno por minuto

    people = [s1, s2, s3, s4, s5]
    res = save_people(people, C, t)
    print(res)