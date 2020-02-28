#include "../include/decompositions/KPeakDecomposition.hpp"
#include <networkit/centrality/CoreDecomposition.hpp>
#include <memory>
#include <iostream>


namespace NetworKit {

KPeakDecomposition::KPeakDecomposition(const Graph &G): Centrality(G){
    //copy the grap into another variable
    //since it will be modified by this method
    std::unique_ptr<Graph> G_(new Graph(G));

    //crete the core-decomposition object
    std::unique_ptr<CoreDecomposition> core_deco(new CoreDecomposition(*G_));

    do {
        //compute core decomposition
        core_deco->run();

        //ranking, pairs <node, score> increasing order
        std::vector<std::pair<node, double>> ranking = core_deco->ranking();

        //remove the degeneracy
        double max_score = ranking[ranking.size-1].second;
        double score;
        node v; 
        for(uint i=0 ; i<ranking.size ; i++){
            std::tie(v, score) = ranking[ranking.size-1-i];
            if(score < max_score)
                break;
            G_->removeNode(v);
        }

    }while(!G_->isEmpty());

    G_.reset();
}


}