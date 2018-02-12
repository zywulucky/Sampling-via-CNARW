# Sampling-via-CNARW
Walking with Perception: Efficient Random Walk Sampling via Common Neighbor Awareness

To let readers have a good understand about our codes, we now give a detail description by following two steps. In the first step, we describe the function of each code file, and in the second step, we show how to execute the codes based on some example.

Note that, we implement all the related algorithms by using C++. We've also written some scripts that help us better control the execution of algorithms.

The First step:
  The role of related folders.
    CNRW_version:　this folder contains four files related to the algorithm CNRW:　CNRW_RelativeError_Age.cpp, CNRW_RelativeError_Degree.cpp, CNRW_converge_Degree.cpp and CNRW_converge_PairSimilarity.cpp. In particular,
       CNRW_RelativeError_Age.cpp:　Given a query cost budget, esimate the proportion of interest in a product at a given age. And output relative error.
       CNRW_RelativeError_Degree.cpp：Given a query cost budget, esimate the average degree of the corresponding graph. And output relative error.
       CNRW_converge_Degree.cpp:　get the convergence to mean of CNRW when using the node degree as indicator of convergence.
       CNRW_converge_PairSimilarity.cpp: get the convergence to mean of CNBRW when using the node pair similarity as indicator of convergence. meanwhile, the node pair similarity is computed by utilizing Jaccard coefficient.
       
       
