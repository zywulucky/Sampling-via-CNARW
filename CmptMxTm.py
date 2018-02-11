#!/usr/bin/python
import sys
from os.path import isfile
import math

def compute_mixing_time(path):
    """
    compute the mixing time from a txt file with data format: "ID data"
    :param string path: the path of data file
    :return: float mixing_time
    """
    z1 = 1
    with open(path, "r") as file:
        for i, line in reversed(list(enumerate(list(file)))):
            z = math.fabs(float(line.split()[1]))
            mixing_time = float(line.split()[0])
            if z <= 0.1:
                if i != 0:
                    z1 = z
                    sum_id = mixing_time
                else:
                    return mixing_time
            else:
                if z1 <= 0.1:
                    sum_id += mixing_time
                    return sum_id / 2.0
                else:  # when z of the last sample is bigger than 0.2 (not converging)
                    return -1
                    
if __name__ == '__main__':
    # sys.argv = [File_name, RW_type, Min_h, Max_h, Graph_name, Sample_num, outputfile]
    # file name format: MyRW/H=3/DBLP_20/zp1.txt RW/DBLP_20/zp1.txt
    # loop h
    f = open("./ttmpdata.txt", "w")
    for item in range(int(sys.argv[2]), int(sys.argv[3]) + 1):
        tm_arr = list()
        # loop sample_num
        for num in range(int(sys.argv[5])):
            if sys.argv[1] == 'ORW':
                path = sys.argv[1] + "/H=" + str(item) + '/' + sys.argv[4] + '/zp' + str(num + 1) + '.txt'
            else:
                path = sys.argv[1] + '/' + sys.argv[4] + '/zp' + str(num + 1) + '.txt'
            if isfile(path):
                tm_arr.append(compute_mixing_time(path))
        # delete the unvalid data, the max and min in mixing time and compute the average
        for i in range(0, len(tm_arr)):
            print '[' + str(i+1) + ',' + str(tm_arr[i]) + ']',
            f.write(str(tm_arr[i]) + "\n")
        print '\n'

        f.close()

        tm_arr.sort()
        print 'total repeat numbers: ' + str(len(tm_arr))
        summ = 0.0
        tmpcount = 0
        for i in range(0,len(tm_arr)):
            if tm_arr[i] == -1:
                continue
            else:
                summ = summ + tm_arr[i]
                tmpcount = tmpcount + 1
        print 'numbers of no convergence: ' + str(len(tm_arr) - tmpcount)
        mx_tm = summ / tmpcount
        #a = int(len(tm_arr) * 0.05)
        #print (a)
        #tm_arr = tm_arr[a:-a]
        #print (tm_arr)
        # tm_arr = tm_arr[1:-1][0:int(sys.argv[5])-10]
   #     mx_tm = sum(tm_arr, 0.0) / len(tm_arr)
        variance = 0.0
        for i in range(0,len(tm_arr)):
            if tm_arr[i] != -1:
                variance += abs(tm_arr[i]-mx_tm)**2
        variance = variance / (tmpcount - 1)
        variance = math.sqrt(variance)
        print 'Varicance is: ' + str(variance)

        with open(sys.argv[6] + '/data.txt', 'a') as f:
            f.write(str(item) + ' ' + str(mx_tm) + '\n' + 'Varicance_' + str(item) + ' ' + str(variance) + '\n')
