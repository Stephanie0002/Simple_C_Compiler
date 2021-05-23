'''
usage: $ cc\test> py .\run_test.py
'''
import glob
import os
import subprocess

def main():
    os.chdir('../code')
    for path in glob.glob('../test/functional_test/08_c*.sc'):
        try:
            p = subprocess.run(['./cc.exe', 'false', path], timeout=5, 
                            check=True, encoding='utf-8', stdout=subprocess.PIPE)
        except subprocess.TimeoutExpired as e:
            print("TimeoutExpired")
            print(e.output)
        else:
            if "error" in p.stdout:
                print(p.stdout)
            else:
                p = subprocess.run(['py', 'main.py', path.rsplit('\\')[-1]+"_node_tree.txt"],
                                check=True, encoding='utf-8', cwd='viewTree', stdout=subprocess.PIPE)
        break #TODO


if __name__ == '__main__':
    main()
