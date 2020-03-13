#ifndef  EDGE_SUPP_CENTRALITY_HPP_
#define  EDGE_SUPP_CENTRALITY_HPP_

#include <networkit/centrality/Centrality.hpp>
#include <vector>

namespace NetworKit {

  class EdgeSupportCentrality: public Centrality {
  public:

    class Triangle {
    public:
      Triangle();
      Triangle(std::vector<node>&& nodes);

      bool operator==(const Triangle& other) const;

      bool operator!=(const Triangle& other) const;

      bool operator<(const Triangle& other) const;
      
      node u,v,z;
            
    };
    
    EdgeSupportCentrality(const Graph& G, bool save=true);

    void run() override;

    /**
     * Set the source node of 
       the edge we want to kno the support.
       it is needed to have a similar interface to
       the one of each Centrality object.
       For instance, if you need to compute the score
       of an edge <u,v> you need to call set_source(u)
       first, then you can call score(v)
     */
    void set_source(node src);

    int compute_support(node src, node trg);

    int compute_support(edgeid edge);

  protected:

    //wether or not to save the triangle associated 
    bool save;

    //current source node file
    node current_src;

    //store the id of  each triangle an edge is involved in
    std::vector<std::vector<int>> edgeIdTriangles;

    //triangles - the position corresponds to the id of a triangle
    std::vector<Triangle> triangles;
    
  };

}





#endif
