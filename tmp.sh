#!/bin/bash
RW_T=ORW
GRAPH=DBLP

for ((i=2; i<=2; ++i)); do
        make -f Makefile_ORW clean
        make -f Makefile_$RW_T RW=${RW_T}/H\=${i} P=${GRAPH} H=${i}
        #make -f Makefile_$RW_T RW=${RW_T} P=${GRAPH} H=${i}
        python3 test3.py $GRAPH $RW_T 1 300 
done
