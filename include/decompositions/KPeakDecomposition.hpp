#ifndef KPEAK_DECO_HPP_
#define KPEAK_DECO_HPP_

#include <networkit/centrality/Centrality.hpp>

namespace NetworKit{


class KPeakDecomposition: public Centrality {
public:

    KPeakDecomposition(const Graph& G);

    void run() override;

protected:
    
    int h;
    int maxCore;

};

}

#endif