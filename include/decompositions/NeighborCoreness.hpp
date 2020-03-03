#ifndef NEIGHCORE_DEC_HPP_
#define NEIGHCORE_DEC_HPP_

#include <networkit/centrality/Centrality.hpp>

namespace NetworKit {

class NeighborCoreness: public Centrality {
public:

    NeighborCoreness(const Graph& G, int depth=1);

    void run() override;

protected:

    int depth; //the depth level for the neighborhood exploration

};
}


#endif