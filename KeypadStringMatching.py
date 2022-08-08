
keynums=[[],[],
['a','b','c'],
['d','e','f'],
['g','h','i'],
['j','k','l'],
['m','n','o'],
['p','q','r','s'],
['t','u','v'],
['w','x','y','z']
]

class TrieNode:
    def __init__(self, value):
        self.value = value
        self.terminates = False
        self.children = {}
    
    def add(self, string):
        if not string: return
        current = string[0]

        if len(string) == 1:
            self.terminates = True

        if current not in self.children:
            self.children[current] = TrieNode(current)

        self.children[current].add(string[1:]) 
    
def get_matching_words(number:str, dictionary:list[str])->list[str]:
    stack = []
    result = []
    root = TrieNode(0)

    for word in dictionary:
        root.add(word)

    stack.append([root, ""])

    while len(stack)>0:
        node, partial = stack.pop()
        if not node: continue

        if len(partial) == len(number):
            result.append(partial)
            continue

        digit = ord(number[len(partial)]) - ord('0')
        characters = keynums[digit]
        for char in characters:
            if char in node.children:
                nextNode = node.children[char]
                nextPartial = partial + char
                stack.append([nextNode, nextPartial])
        
    return result

if __name__=="__main__":
    dictionary = []

    with open('/Users/Aarya/Development/four-letter-words.txt','r',encoding='utf-8') as file:
        for line in file:
            dictionary.append(line)
    
    print(get_matching_words('8733',dictionary))

