class AhoNode:
    def __init__(self):
        self.goto = {}
        self.out = []
        self.fail = None


def aho_create_forest(patterns):
    root = AhoNode()

    for path in patterns:
        node = root
        for symbol in path:
            node = node.goto.setdefault(symbol, AhoNode())
        node.out.append(patterns.index(path))
    return root


def aho_create_state_machine(patterns):
    root = aho_create_forest(patterns)
    queue = []
    for node in root.goto.values():
        queue.append(node)
        node.fail = root

    while len(queue) > 0:
        rnode = queue.pop(0)

        for key, unode in rnode.goto.items():
            queue.append(unode)
            fnode = rnode.fail
            while fnode is not None and key not in fnode.goto:
                fnode = fnode.fail
            unode.fail = fnode.goto[key] if fnode else root
            unode.out += unode.fail.out

    return root


def aho_find_all(string, root, patterns):
    node = root
    output = [[] for i in patterns]

    for i in range(len(string)):
        while node is not None and string[i] not in node.goto:
            node = node.fail
        if node is None:
            node = root
            continue
        node = node.goto[string[i]]
        for p in node.out:
            output[p].append(i - len(patterns[p]) + 2)

    return output


def aho_find_chains(splits, coords, maxlen, joker, string):
    chain = splits[0]

    for i in range(len(coords) - 1):
        curr_line = chain
        next_line = splits[coords[i + 1][1]]
        chain = []
        for j in range(len(curr_line)):
            if next_line.count(curr_line[j] + coords[i + 1][0] - coords[i][0]) > 0:
                flag = 1
                for k in range(curr_line[j], curr_line[j] + coords[i + 1][0] - coords[i][0] - 1):
                    if string[k] == joker:
                        flag = 0
                        break
                if flag == 1:
                    chain.append(curr_line[j] + coords[i + 1][0] - coords[i][0])

    nchain = []
    for i in range(len(chain)):
        if 0 < chain[i] - coords[-1][0] < maxlen + 2:
            nchain.append(chain[i] - coords[-1][0])

    return nchain


def str_split(string, joker):
    flag = 1
    temp = []
    cord = []
    string += joker
    for i in range(len(string)):
        if string[i] != joker:
            if flag == 1:
                flag = 0
                cord.append([i])
                temp.append(string[i])
            else:
                temp[-1] += string[i]
        else:
            if flag == 0:
                flag = 1
                if temp.count(temp[-1]) > 1:
                    cord[-1].append(temp.index(temp[-1]))
                    temp.pop(-1)
                else:
                    cord[-1].append(len(temp) - 1)

    return temp, cord

print("Введите строку для обработки:", end="  ")
string = str(input())
print("Введите шаблон поиска:", end="  ")
template = str(input())
print("Введите символ-джокер шаблона поиска:", end="  ")
joker = str(input())
print("Введите символ, который не может быть на месте символа-джокера:", end="  ")
blocked = str(input())

templates, positions = str_split(template, joker)
root = aho_create_state_machine(templates)
output = aho_find_all(string, root, templates)
result = aho_find_chains(output, positions, len(string) - len(template), blocked, string)

print("\nРезультат:")
for i in result:
    print(i)