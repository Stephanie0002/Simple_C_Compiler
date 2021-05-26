'''
usage: $ cc\test> py .\run_test.py
'''
import glob
import os
import subprocess
from pprint import pprint

def main():
    os.chdir('../code')
    for path in glob.glob('../test/functional_test\\19_neg_expr.sc'):
        fileBasenameNoExtension = path.rsplit('\\')[-1]
        print(f"testing w/ {fileBasenameNoExtension}")
        try:
            p = subprocess.run(['./cc.exe', 'false', path], timeout=5,
                            check=True, encoding='utf-8', stdout=subprocess.PIPE)
        except (subprocess.TimeoutExpired, subprocess.CalledProcessError) as e:
            print(e)
            print(e.output)
        else:
            if "error" in p.stdout:
                print(p.stdout)
            else:
                # seems that graphviz won't update timestamp of existing img
                p = subprocess.run(['py', 'main.py', '-path', fileBasenameNoExtension+"_node_tree.txt"],
                                check=True, encoding='utf-8', cwd='viewTree', stdout=subprocess.PIPE)


if __name__ == '__main__':
    main()
