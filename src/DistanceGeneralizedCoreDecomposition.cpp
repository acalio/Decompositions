#include "../include/decompositions/DistanceGeneralizedCoreDecomposition.hpp"
#include "../include/decompositions/hDegreeCentrality.hpp"
#include <networkit/graph/BFS.hpp>
#include <memory>
#include <iostream>

namespace NetworKit {

DistanceGeneralizedCoreDecomposition::DistanceGeneralizedCoreDecomposition(const Graph &G, int h_):Centrality(G), h(h_), maxCore(0){}


void DistanceGeneralizedCoreDecomposition::run(){
       /* Main data structure: buckets of nodes indexed by their remaining degree. */
    index z = G.upperNodeIdBound();
    std::vector<node> queue(G.numberOfNodes());
    std::vector<index> nodePtr(z);
    std::vector<index> degreeBegin(G.numberOfNodes());
    std::vector<count> degree(z);       // tracks degree during algo
    std::vector<std::unordered_set<node>> reach_set;
    
    //copy the graph into another variable
    std::unique_ptr<Graph> G_ = std::make_unique<Graph>(G);

    bool directed = G.isDirected();

    /* Bucket sort  by degree */
    /* 1) bucket sizes */
    HDegreeCentrality hdeg(G,h,true);
    hdeg.run();
    G.forNodes([&](node u){
        degree[u] = hdeg.score(u);
        ++degreeBegin[degree[u]];
    });

    reach_set.swap(hdeg.getReachSets());

    index sum = 0; // 2) exclusive in-place prefix sum
    for (index i = 0; i < degreeBegin.size(); ++i) {
        index tmp = degreeBegin[i];
        degreeBegin[i] = sum;
        sum += tmp;
    }

    /* 3) Sort nodes/place them in queue */
    G.forNodes([&](node u) {
        count deg = degree[u];
        index pos = degreeBegin[deg];
        ++degreeBegin[deg];
        queue[pos] = u;
        nodePtr[u] = pos;
    });



    /* 4) restore exclusive prefix sum */
    index tmp = 0; // move all one forward
    for (index i = 0; i < degreeBegin.size(); ++i) {
        std::swap(tmp, degreeBegin[i]);
    }

    /* Current core and and computed scoreData values. */
    index core = 0;
    scoreData.clear();
    scoreData.resize(z);

    /* Main loop: Successively "remove" nodes by setting them not alive after processing them. */
    /* From now on we work on the copy of the graph */
    for (index i = 0; i < G.numberOfNodes(); ++i) {
        node u = queue[i];
        core = std::max(core, degree[u]); // core is maximum of all previously seen degrees
        
        scoreData[u] = core;
        G_->removeNode(u);
        /* Remove a neighbor by decreasing its degree and changing its position in the queue */
        auto removeNeighbor = [&](node v) {
            if (nodePtr[v] > i) { // only nodes that are after the current node need to be considered
                // adjust the degree
                count oldDeg = degree[v];
                count newDeg = -1;              
                Traversal::BFSfromWithLimit(*G_, v, h, [&](node u, count dis){
                    newDeg++;
                });

                degree[v] = newDeg; 
                
                while(oldDeg>newDeg){
                    // Degrees smaller than the current degree can be before the current position
                    // Correct those that we need. Note that as we decrease degrees only by one
                    // all degreeBegin values larger than oldDeg will have been adjusted already.
                    if (degreeBegin[oldDeg] <= i) {
                        degreeBegin[oldDeg] = i + 1;
                    }

                    if (degreeBegin[newDeg] <= i) {
                        degreeBegin[newDeg] = i + 1;
                    }

                    // Swap v with beginning of the current bucket.
                    index oldPos = nodePtr[v];
                    index newPos = degreeBegin[oldDeg];

                    node nodeToSwap = queue[newPos];
                    std::swap(queue[oldPos], queue[newPos]);
                    std::swap(nodePtr[nodeToSwap], nodePtr[v]);

                    // Move bucket border, v is now in the previous bucket, i.e. the bucket of its new degree
                    ++degreeBegin[oldDeg];
                    oldDeg--;
                }
            }
        };

        /* Remove u and its incident edges. */
        for(auto neig : reach_set[u])
            if(G_->hasNode(neig))
                removeNeighbor(neig);
        
        
    }

    maxCore = core;

    hasRun = true;
}


}
