
# Return boolean indicating if some numbers from given array can add up to target
def canSum(target, arr):
    dp = [False] * (target + 1)
    dp[0] = True

    for i in range(target):
        if dp[i]:
            for num in arr:
                future = num + i
                if future < len(dp):
                    dp[future] = True

    return dp[target]


# Return array containing any combination of numbers from arr that add up to target
def howSum(target, arr):
    prev = [None] * (target + 1)
    dp = [False] * (target + 1)

    dp[0] = True

    for i in range(target):
        if dp[i] == True:
            for num in arr:
                if num + i < len(dp):
                    dp[num + i] = True
                    prev[num + i] = i

    if dp[target] == False:
        return None

    path = []
    current = target

    while current:
        path.append(current - prev[current])
        current = prev[current]

    return path


# Return array containing shortest combination adding up to target
def bestSum(target, arr):
    prev = [None] * (target + 1)
    dp = [False] * (target + 1)

    dp[0] = True

    for i in range(target):
        if dp[i] == True:
            for num in arr:
                if num + i < len(dp):
                    dp[num + i] = True
                    # keep smaller value as longer jump means fewer numbers
                    if prev[num + i] == None or prev[num + i] > i:
                        prev[num + i] = i

    if dp[target] == False:
        return None

    path = []
    current = target

    while current:
        path.append(current - prev[current])
        current = prev[current]

    return path


# Return boolean indicating if target string can be constructed 
# from the items in string array by concatanating them
def canConstruct(target, array):
    dp = [False] * (1 + len(target))
    dp[0]=True

    for i in range(len(target)):
        if dp[i] == True:
            for word in array:
                if len(word) - 1 + i >= len(target):
                    continue
                if target[i:i+len(word)] == word:
                    dp[i + len(word)] = True

    return dp[len(target)] == True

def countConstruct(target, array):
    dp = [0] * (1 + len(target))
    dp[0] = 1

    for i in range(len(target)):
        if dp[i] > 0:
            for word in array:
                if len(word) - 1 + i >= len(target):
                    continue
                if target[i:i+len(word)] == word:
                    dp[i + len(word)] += 1

    return dp[len(target)]

def allConstruct(target, array):
    dp = [None] * (1 + len(target))

    for i in range(len(dp)):
        dp[i] = []
    
    dp[0] = [[]]

    for i in range(len(target)):
        for word in array:
            if i + len(word) - 1 < len(target) and target[i:i+len(word)] == word:
                for subArray in dp[i]:
                    newList = [*subArray, word]
                    dp[i + len(word)].append(newList)

    return dp[len(target)]


if __name__=="__main__":
    print(canSum(7, [5])) # false
    print(canSum(7, [5, 3, 4])) # true 3 + 4
    print(howSum(7, [5, 3, 4])) # 3 + 4
    print(bestSum(7, [5, 3, 4, 7])) # 7
    print(canConstruct("ABCDEF", ["AB","ABC","CD","DEF","ABCD"])) # true ABC + DEF
    print(canConstruct("ABCDEF", ["AB","ABC","CD","EF","ABCD"])) # true ABCD + EF
    print(canConstruct("ABCDEF", ["AB","BC","CD","DEF"])) # false
    print(countConstruct("abcdef", ["ab","cd","ef","abc","def","abcdef"])) # 3
    print(allConstruct("abcdef", ["ab","cd","ef","abc","def","abcdef"])) # 3
