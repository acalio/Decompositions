# Introduction 

This project is related to the following paper:

    >  Cores matter? An analysis of graph decomposition effects on influence maximization problem  
A. Caliò, A. Tagarelli, F. Bonchi
        

published at the 12th ACM Web Science Conference (WebSci) 2020.

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
    ./deco input-graph output-graph decomposition-algorithm
    

- input-graph: is an edgelist file containing a directed (potentially weighted) network.
- output-file: the file where the results are saved
- decomposition-algorithm: one of the available decomposition

For instance, if you need to carry out a core-decomposition:

    ./deco input-edgelist results.txt kcore
    
The program will store in results.txt the output of the computation.
More specifically, in this case the file will contain a line <vertex id, core-index>
for each node in the network.

There are many other options available. To have a more comprehensive guide
issue the command:
    
    ./deco --help
