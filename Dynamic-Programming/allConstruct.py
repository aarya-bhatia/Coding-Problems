
def allConstruct(target, wordBank, memo={}):
    if target in memo:
        print("hit")
        return memo[target]

    if not target:
        return [[]]
    
    result = []

    for prefix in wordBank:
        if target.startswith(prefix):
            offset = len(prefix)
            suffixArray = allConstruct(target[offset:], wordBank)
            for arr in suffixArray:
                result.append([prefix] + arr)

    memo[target] = result
    return result


if __name__ == "__main__":
    while True:
        try:
            target = input("Enter target:")
            wordBank = []
            while True:
                try:
                    word = input("Word bank entry:")
                    wordBank.append(word)

                except KeyboardInterrupt:
                    print()
                    break

            results = allConstruct(target, wordBank)
            print(results)

        except KeyboardInterrupt:
            print()
            break

    print("Exit Program")

        
