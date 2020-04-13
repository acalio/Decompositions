
#include "../include/decompositions/NeighborCoreness.hpp"
#include <memory>
#include <networkit/centrality/CoreDecomposition.hpp>
#include <networkit/graph/BFS.hpp>

namespace NetworKit {

NeighborCoreness::NeighborCoreness(const Graph& G, int depth)
        :Centrality(G), depth(depth){}


void NeighborCoreness::run() {

    index z = G.upperNodeIdBound();
    scoreData.clear();
    scoreData.resize(z);
    //    std::unique_ptr<CoreDecomposition> core_deco = 
    //                                std::make_unique<CoreDecomposition>(G, false, true, false, CoreDecomposition::Direction::Out);
    CoreDecomposition core_deco(G, false, true, false, CoreDecomposition::Direction::Out);
    //run core decomposition
    core_deco.run();

    //aggregate the result
    G.parallelForNodes([&](node u){
        scoreData[u] = core_deco.score(u);
        Traversal::BFSfromWithLimit(G, u, depth, [&](node v, count dis){
            if(v!=u)
                scoreData[u] += core_deco.score(v);
        });
    });

    hasRun = true;
}
}

