import sys

if __name__ == '__main__':

    qc = 0.0
    count = 0
    path = './qc3.txt' 
    print path
    for line in open(path,"r"):
#        tmp = line.strip("\n").split(" ")
        qc = qc + float(line)
        count = count + 1

    qc = qc * 1.0 / count
    print qc

