#include "../include/decompositions/KPeakDecomposition.hpp"
#include <networkit/centrality/CoreDecomposition.hpp>
#include <memory>
#include <iostream>


namespace NetworKit {

KPeakDecomposition::KPeakDecomposition(const Graph &G): Centrality(G){}

void KPeakDecomposition::run(){
    //copy the grap into another variable
    //since it will be modified by this method
    index z = G.upperNodeIdBound();
    scoreData.clear();
    scoreData.resize(z);
    std::unique_ptr<Graph> G_ = std::make_unique<Graph>(G);

    //crete the core-decomposition object
    CoreDecomposition core_deco(*G_, false, true, false, CoreDecomposition::Direction::Out);
    int iteration = 0;
    do {
        //compute core decomposition
        core_deco.run();

        //ranking, pairs <node, score> increasing order
        std::vector<std::pair<node, double>> ranking = core_deco.ranking();

        //get the value for the degeneracy
        double maxScore = ranking[0].second;
        std::cout << "Degeneracy "<< maxScore << " it: " << iteration++<<std::endl;
        double score;   
        node v; 

        for(uint i=0 ; i<ranking.size() ; i++){
            std::tie(v, score) = ranking[i];
            if(score < maxScore)
                break;
            G_->removeNode(v);
            
            scoreData[v] = score;
        }
        maxCore = maxCore>maxScore? maxCore: maxScore;
    } while(!G_->isEmpty());


    hasRun = true;
}


}
