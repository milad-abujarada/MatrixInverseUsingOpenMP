# LU Decomposition method to generate Matrix Inverse
This is a project I did in a Computer Architecture class when I was student at the University of Colorado Denver.

## Introduction
Data security is one of the thriving areas in computer science. This area depends profoundly on mathematical computations such as matrix inverse to encrypt and decrypt data. In this project I portray the speed gained in using openMP, a parallel programming API, in calculating large matrices inverses using multiple CPUs and different number of threads. The results of using openMP is compared to the result of a sequential approach written using C++.

## The execution enviornment
The execution of the implementation toke place on a cluster machine called Hydra.

## Hydra
Hydra is cluster machine belongs to UCD consists of 17 nodes (1 master node and 16 computing nodes). The master node is the one responsible for distributing the work load between computing nodes. When all computations are done the master node collects the results and sends it to the external node who requested the tasks. The nodes of the cluster are connected to each other via an InfiniBand switch and Gigabit switch. Each of these nodes is equipped with two processors each processor consists of 6 cores. However, this is only the case of the nodes from 0 – 11. In addition to the 12 cores per node, the nodes from 12-15 are also equipped with 2 NVIDA Tesla Fermi S 2050 GPU servers; each GPU server has 448 CUDA cores. The operating system that’s deployed on the cluster is Linux version 2.6.18. The cluster has a speed of 2.2 GHz, L1 instruction cache of 6 × 64KB, L1 data cache of 6 × 64KB, L2 cache 6 × 512KB, and L3 cache of 6MB per processor. This kind of machine can be used to implement different kind of applications specially the one that requires parallel computing or have large amount of data. The way this kind of applications is implemented is either by dividing the tasks on nodes, but this requires no existence of dependency between the tasks, or by dividing the data into blocks and then the same task can be performed on these blocks by each node. Examples of these applications are large matrixes multiplications, processing of large amount of data that has been retrieved by satellites or sensors, and implementing applications that are related to DNA processing.

## The results
![](https://github.com/milad-abujarada/MatrixInverseUsingOpenMP/blob/master/results.png)
