
def gridTraveler(m,n):
    table = [[0] * n] * m
    table[1][1] = 1

    for i in range(0, m-1):
        for j in range(0, n-1):
            table[i][j+1]+=table[i][j]
            table[i+1][j]+=table[i][j]

    result = table[m-1][n-1]
    print(result)
    return result


gridTraveler(3, 3)
gridTraveler(3, 2)
gridTraveler(18, 18)
