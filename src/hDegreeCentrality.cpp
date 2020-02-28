#include "../include/decompositions/hDegreeCentrality.hpp"
#include <networkit/graph/BFS.hpp>
#include <iostream>
#include <chrono>

namespace NetworKit {

HDegreeCentrality::HDegreeCentrality(const Graph& G, int h_, bool save_reachable_set_, bool normalized, bool outDeg, bool ignoreSelfLoop)
    :DegreeCentrality(G, normalized, outDeg, ignoreSelfLoop),h(h_), save_reachable_set(save_reachable_set_){
        if(save_reachable_set){
            reach_set = std::vector<std::unordered_set<node>>(G.upperNodeIdBound());
        }
            
    }


void HDegreeCentrality::run() {
    scoreData = std::vector<double>(G.upperNodeIdBound(), -1.0);
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    G.parallelForNodes([&](node u){
        Traversal::BFSfromWithLimit(G, u, h, [&](node v, count dis){
            scoreData[u]++;
            if(save_reachable_set)
                #pragma omp critical
                reach_set[v].insert(u);
        });
    });
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
    hasRun = true;
}

std::unordered_set<node> &HDegreeCentrality::getReachSet(node v){ 
    assureFinished();
    assureReachSet();
    return reach_set[v];
}

std::vector<std::unordered_set<node>> &HDegreeCentrality::getReachSets(){
    assureFinished();
    assureReachSet();
    return reach_set;    
}

void HDegreeCentrality::assureReachSet() {
    if(!save_reachable_set) throw std::runtime_error("Reachable set have not been saved");
}

};