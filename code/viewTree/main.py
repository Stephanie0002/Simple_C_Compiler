from graphviz import Digraph

file_name = 'tree.txt'

with open(file_name, 'r') as file:
    items = file.read().split()
    print(items)

g = Digraph('G', filename='tree.gv',format='png')
for i in range(0, len(items), 2):
    g.node(items[i], items[i+1])
    if (i/2) % 2 == 1:
        g.edge(items[i-2], items[i])
print(g.source)
g.view()
g.render()
