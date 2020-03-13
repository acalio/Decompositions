#include "../include/decompositions/EdgeSupportCentrality.hpp"

namespace NetworKit {

  EdgeSupportCentrality::EdgeSupportCentrality(const Graph& G, bool save):Centrality(G), save(save), current_src(-1){}
  
  void EdgeSupportCentrality::set_source(node src) {
    current_src = src;
  }

  void EdgeSupportCentrality::run() {
    index z = G.upperEdgeIdBound();
    edgeIdTriangles.resize(z);
    
    G.forEdges([&](node u, node v){
        
    });
  }

  
  int EdgeSupportCentrality::compute_support(node src, node trg){
    int eid = G.edgeId(src, trg);
    int support = 0;
    G.forInNeighborsOf(src, [&](node v){
        if(G.hasEdge(trg, v))
          support++;
    });
    

    
    return compute_support(eid);
  }

  int EdgeSupportCentrality::compute_support(edgeid edge){
    
    return 0;
  }


}

