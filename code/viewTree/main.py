import argparse
from graphviz import Digraph

def gen_Digraph(file_name):
    with open(file_name, 'r') as file:
        items = file.read().split()
        print(items)

    g = Digraph('G', filename=file_name.replace('.txt', '.gv'), format='png')
    for i in range(0, len(items), 2):
        g.node(items[i], items[i+1])
        if (i/2) % 2 == 1:
            g.edge(items[i-2], items[i])
    # print(g.source)
    # g.view()
    g.render()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-path", nargs=1, action='append', help="path of *_node_tree.txt")
    args = parser.parse_args()
    # print(vars(args)['path'][0])
    list = vars(args)['path']
    for i in range(0,len(list)):
        gen_Digraph(list[i][0])


if __name__ == '__main__':
    main()
