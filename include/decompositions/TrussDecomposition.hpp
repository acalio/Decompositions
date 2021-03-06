#ifndef TRUSSDECOMPOSITION_HPP_
#define TRUSSDECOMPOSITION_HPP_


#include <networkit/centrality/Centrality.hpp>

namespace NetworKit {

class TrussDecomposition: public Centrality {
public:

  TrussDecomposition(const Graph& G);

  void run() override;
  
  
};
}

#endif
