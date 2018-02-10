import sys
import os
import time


def ORW(alpha, path):
    commd = './MyRW -dataset ' + str(path) + ' -ID ' + str(alpha)
    print(commd)
    p = os.popen(commd, 'r')
    while 1:
        line = p.read()
        if line == '':
            break
        print(line)
    p.close()


def RW(alpha, path):
    commd = './RW -dataset ' + str(path) + ' -ID ' + str(alpha)
    print(commd)
    p = os.popen(commd, 'r')
    while 1:
        line = p.read()
        if line == '':
            break
        print(line)
    p.close()

def NBRW(alpha, path):
    commd = './NBRW -dataset ' + str(path) + ' -ID ' + str(alpha)
    print(commd)
    p = os.popen(commd, 'r')
    while 1:
        line = p.read()
        if line == '':
            break
        print(line)
    p.close()

def CNRW(alpha, path):
    commd = './CNRW -dataset ' + str(path) + ' -ID ' + str(alpha)
    print(commd)
    p = os.popen(commd, 'r')
    while 1:
        line = p.read()
        if line == '':
            break
        print(line)
    p.close()

if __name__ == '__main__':
    path = './dataset/'+ sys.argv[1] +'.txt'
    rw = {"ORW":ORW, "RW":RW, "NBRW":NBRW, "CNRW":CNRW}
    c = int(sys.argv[4])
    for alpha in range(int(sys.argv[3]), c+1):
        rw[sys.argv[2]](alpha, path)
        time.sleep(2)
    print('finish')
