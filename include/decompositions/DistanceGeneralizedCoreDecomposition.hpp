#ifndef DISTANCEGENERALIZED_COREDECO_HPP_
#define DISTANCEGENERALIZED_COREDECO_HPP_

#include <networkit/centrality/Centrality.hpp>

namespace NetworKit{


class DistanceGeneralizedCoreDecomposition: public Centrality {
public:

    DistanceGeneralizedCoreDecomposition(const Graph& G, int h_);

    void run() override;

protected:
    
    int h;
    int maxCore;

};

}

#endif