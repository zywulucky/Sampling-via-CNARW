# Sampling-via-CNARW
Walking with Perception: Efficient Random Walk Sampling via Common Neighbor Awareness

To let readers have a good understand about our codes, we now give a detail description by following two steps. In the first step, we describe the function of each code file, and in the second step, we show how to execute the codes based on some example.

Note that, we implement all the related algorithms by using C++. We've also written some scripts that help us better control the execution of algorithms.

First step:

CNRW_version:　this folder contains four files related to the algorithm CNRW, they are,
    
CNRW_RelativeError_Age.cpp: Given a budget of query cost, esimate the proportion of interesting in a product at a given age. And output relative error.
       
CNRW_RelativeError_Degree.cpp: Given a budget of query cost, esimate the average degree of corresponding graph. And output relative error.
       
CNRW_converge_Degree.cpp: Get "the convergence to mean" of CNRW when use node degree as the indicator of convergence.
       
CNRW_converge_PairSimilarity.cpp: Get the "convergence to mean" of CNBRW when use node pair similarity as the indicator of convergence. The node pair similarity is computed by utilizing Jaccard coefficient.
   
NBRW_version: this folder contains five files related to the algorithm NBRW, they are,
        
NBRW_RelativeError_Age.cpp: The function is similar to CNRW_RelativeError_Age.cpp.
     
NBRW_converge_PairSimilarity.cpp: The funciton is similar to CNRW_converge_PairSimilarity.cpp
        
NBRW_RelativeError_Degree.cpp：The function is similar to CNRW_RelativeError_Degree.cpp.
   
NBRW_converge_Degree.cpp: The function is similar to CNRW_converge_Degree.cpp.
        
NBRW_RelativeError_PairSimilarity.cpp:　Given a budget of query cost, estimate the average node pair similarity of corresponding graph. And output relative error.
   
ORW_version: This folder contains five files which related to our algorithm CNARW. The function of these five files is similar to files in NBRW_version.

RW_version: This folder contains five files which related to the algorithm SRW. The functioin of these five files is similar to files in RW_version.

Convergence: This folder implements the Geweke diagnostic.

sfmt: This folder is used to generate random numbers.

RW.cpp, NBRW.cpp, CNRW.cpp and MyRW_H=1.cpp (implement of CNARW) is one file of RW_version, NBRW_version, CNRW_version and ORW_version respectively. The only difference is that the name is different. One can compile them by using Makefile_RW, Makefile_NBRW, Makefile_CNRW and Makefile_ORW respectively.

ComputeBurnin_tmp.h: Compute the "covergence to mean" and write the result in specified path.

fileProcess.h: Taking the graph dataset as input, and storage them in data structue.

comptAvgSimlar.cpp: Compute the average node pair similarity of corresponding graph, and output the result, which is used as the background truth.

generateAge.cpp: Generate the age of each user according to the specified distribution. Note that, readers need to manually set distribution.

generateInterest.cpp: Compute the proportion of users of different age groups of the same product, which is used as the background truth.

datasets.txt: Contain the links to download datasets we used in experiment.

logspace.txt: This is needed when compute the "convergence to mean".

test3.py: Control the execution of different algorithms.

tmp.sh: Control the execution of test3.py.

jspc.py: Statistical experimental results. this scripts help one to get the average relative error.

CmptMxTm.py: Statistical experimental results. this scripts help one to get the average "convergence to mean".

Product_A.txt: Denote the users in Flickr whether are interest in product A　or not. Product_B.txt and Product_C are similar to Product_A.txt.




Second Step:

1. How to compute the average "convergence to mean" by running SRW for 300 times (use Flickr as an example)?

     I. Create a folder, namely "Experiment", then continue creating a folder, namely "RW" in "Experiment".
     
     II. Change the name of RW_converge_Deg.cp to RW.cpp. and keep it and the folder "Experiment" in the same directory.
     
     III. Open tmp.sh. In particular, 
        
              #!/bin/bash
              RW_T=RW
              GRAPH=Flickr

              for ((i=2; i<=2; ++i)); do
                   make -f Makefile_ORW clean
                   #make -f Makefile_$RW_T RW=${RW_T}/H\=${i} P=${GRAPH} H=${i}
                   make -f Makefile_$RW_T RW=${RW_T} P=${GRAPH} H=${i}
                   python3 test3.py $GRAPH $RW_T 1 300 
              done
            
      IV. Run ./tmp.sh
      
      V. Move CmptMxTm.py to the folder "Experiment" and run the following command in linux terminal:
      
               ./CmptMxTm.py RW 1 1 Flickr 300 .
           
      Then, the experimental result is written in "data.txt"
      
      Note that, if you want to run CNARW on Flickr, just run tmp.sh directly.
       

2. After knowing the convergence rate of SRW and giveing a extra budget of query cost, How to estimate the average degree of Flickr in 300 times and recorder the relative error ?

     I. Change the name of RW_RelativeError_Deg.cp to RW.cpp.

     II. Do the following changes:
     
               int burnin = 30000; -> int burnin = the convergence rate you got in question 1.
               
               while(flag_cout <= qc+650)  -> change 650 to the extra budget of query cost you have.
               
               double rr = abs(estimator - 44.45033) / 44.45033; -> change 44.45033 to the average degree of Flickr
               
     III. Save above changes, then open tmp.sh, make corresponding changes, this step is similar to step III of question 1.
     
     IV.  after run ./tmp.sh, one can see a file name "qc.txt" is created. this file recorder the experimental results of 300 times. In this time, one can get the average result by using the following command:  python jsqc.py RW
     
For other functions, the experimental process is similar.
           
         
