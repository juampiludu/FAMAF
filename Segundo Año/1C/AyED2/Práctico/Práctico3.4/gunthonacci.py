def empty_list(n,m):
    list_ = list()
    for i in range(n):
        list_.append([])
        for _ in range(m):
            list_[i].append(0)
    return list_


def gunthonacci(i,j):
    gunth = empty_list(i,j)
    gunth[0][0] = 1
    gunth[0][1] = 1
    gunth[1][0] = 1
    for k in range(1, i):
        for m in range(2,j):
            gunth[0][m] = gunth[i-1][j-3] + gunth[i-1][j-2]
            gunth[k][m-1] = gunth[i-1][j-2] + gunth[i-2][j-1]
        if k < i-1:
            gunth[k+1][0] = gunth[i-3][j-1] + gunth[i-2][j-1]
    return gunth[i-1][j-1]
    
print(gunthonacci(4,4))