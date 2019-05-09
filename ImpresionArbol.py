from collections import namedtuple

Node = namedtuple('Node', 'value left right', defaults=(None, None, None))

tree = Node(6, 
    Node(4, Node(3), Node(5)),
    Node(8, Node(7), Node(9))
)

def height(node):
    if node == None or node.left == node.right == None:
        return 0
    else:
        return max(height(node.left), height(node.right)) + 1

totalHeight = height(tree) + 1
width = 2 ** totalHeight + 1

table = []

for _ in range(totalHeight):
    table.append(['.'] * width)

def computeIndex(depth, offset):
    initialSpacing = 2 ** (totalHeight - depth - 1)
    separation = 2 * initialSpacing - 1
    return initialSpacing + separation * offset + offset

def writeValue(depth, offset, value):
    valueStr = str(value)
    index = computeIndex(depth, offset)
    valueStr
    print(index)
    print(computeIndex(depth + 1, 2 * offset))
    print(computeIndex(depth + 1, 2 * offset + 1))

    for c in valueStr:
        table[depth][index] = c

def traverseFill(node, depth, offset):
    if node != None:
        writeValue(depth, offset, node.value)

        traverseFill(node.left, depth + 1, 2 * offset)
        traverseFill(node.right, depth + 1, 2 * offset + 1)

traverseFill(tree, 0, 0)

for i in range(len(table)):
    print(''.join(table[i]))