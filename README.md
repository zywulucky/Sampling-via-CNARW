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

sfmt: This file is used to generate random numbers.
       
