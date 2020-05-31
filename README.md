# Overview


This project is developed as part of the following research paper:

[A. Caliò, A. Tagarelli, F. Bonchi (2020). Cores matter? An analysis of graph decomposition effects on influence maximization problem. In Procs. of the 12th ACM Web Science Conference (WebSci-2020), July 6th - July 10th, 2020,  Southampton, UK](https://doi.org/10.1145/3394231.3397908).

Please cite the above paper in any research publication you may produce using this code or data/analysis derived from it.


## Abstract
Estimating the spreading potential of nodes in a social network is an
important problem which finds application in a variety of different
contexts, ranging from viral marketing to spread of viruses and
rumor blocking. Several studies have exploited both mesoscale
structures and local centrality measures in order to estimate the
spreading potential of nodes. To this end, one known result in the
literature establishes a correlation between the spreading potential
of a node and its coreness: i.e., in a core-decompostion of a network,
nodes in higher cores have a stronger influence potential on the
rest of the network. In this paper we show that the above result
does not hold in general under common settings of propagation
models with submodular activation function on directed networks,
as those ones used in the influence maximization (IM) problem.
Motivated by this finding, we extensively explore where the
set of influential nodes extracted by state-of-the-art IM methods
are located in a network w.r.t. different notions of graph decom-
position. Our analysis on real-world networks provides evidence
that, regardless of the particular IM method, the best spreaders
are not always located within the inner-most subgraphs defined
according to commonly used graph-decomposition methods. We
identify the main reasons that explain this behavior, which can
be ascribed to the inability of classic decomposition methods in
incorporating higher-order degree of nodes. By contrast, we find
that a distance-based generalization of the core-decomposition for
directed networks can profitably be exploited to actually restrict
the location of candidate solutions for IM to a single, well-defined
portion of a network graph.





# Requirements
In order to compile the project you need:

- A modern C++ compiler
- OpenMP for parallelism 
- Python3
- Cmake - version 3.5. or higher
- Build System [Make]
- [Boost] program_options library


# Installation
Clone this repository as well as the networkit submodule.
    
    cd to/your/path
    git clone https://github.com/acalio/Decompositions.git
    git submodule --recursive init 
    
**Note**: You are supposed to use my forked version of networkit.
I made some changes to the original version that are essential to this project.


You need to compile the project. Follow these steps.

    cd to/your/path
    mkdir build
    cd build
    cmake ..
    make 
    

# Usage
The following steps are needed to run the executable. 

    cd to/your/executable
    ./deco input-graph output-file decomposition-algorithm
    

- input-graph: the path to a file storing the edge-list of a directed (weighted) network
- output-file: the path to a file storing results, i.e., $\langle  v, k \rangle$, where $v$ is the id of a node and $k$ the index assigned by the selected graph-decomposition algorithm
- decomposition-algorithm: specifies a graph-decomposition algorithm. Available options:
_kcore_, _kpeak_, _ktruss_, _neighcoreness_, _dgcore_.

For instance, if you need to carry out a core-decomposition:

    ./deco input-edgelist results.txt kcore
    
The program will store in results.txt the output of the computation.

There are many other options available. To have a more comprehensive guide just
issue the command:
    
    ./deco --help
