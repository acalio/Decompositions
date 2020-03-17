#ifndef  EDGE_SUPP_CENTRALITY_HPP_
#define  EDGE_SUPP_CENTRALITY_HPP_

#include <networkit/centrality/Centrality.hpp>
#include <vector>

namespace NetworKit {

  //forward declaration
  class TrussDecomposition;

  
  class EdgeSupportCentrality: public Centrality {
  public:

    class Triangle {
    public:
      Triangle(std::vector<edgeid>&& eids);

      bool operator==(const Triangle& other) const;

      bool operator!=(const Triangle& other) const;

      std::vector<edgeid>::iterator begin();

      std::vector<edgeid>::iterator end();

      std::vector<edgeid> edges; // edges 

    };
    
    EdgeSupportCentrality(const Graph& G, bool save=true);

    void run() override;
 
    template <bool saveTriagles>
    inline int compute_support(node src, node trg);

    friend class TrussDecomposition;

  protected:

    //wether or not to save the triangle associated 
    bool saveTriangles;

    //current source node file
    node currentSrc;

    //store the id of  each triangle an edge is involved in
    std::vector<std::vector<int>> edgeIdTriangles;

    //triangles - the position corresponds to the id of a triangle
    std::vector<Triangle> triangles;

    //vector of porcessed edges id
    std::vector<bool> processedEdges;
    
  };


  //implementation for saveTriangles == True
  template<bool saveTriangles>
  inline int EdgeSupportCentrality::compute_support(node src, node trg) {
    //compute the support and save the triangles into the
    //the data structures
    edgeid srctrgId = G.edgeId(src, trg);

    if(processedEdges[srctrgId])
      //get the length of the sotre triangles ids with eid
      return edgeIdTriangles[srctrgId].size();

    // compute the support
    G.forInEdgesOf(src, [&](node src,  node u, edgeweight ew, edgeid usrcId){
                          if(processedEdges[usrcId])
                            return;

                         if(G.hasEdge(trg, u)){
                           edgeid trguId = G.edgeId(trg,u);
                           if(processedEdges[trguId])
                             return;
   
                           //it is the first time this triangle is encounter
                           triangles.push_back(Triangle({usrcId, trguId, srctrgId}));

                           //add the triangle id to every edge inovlved
                           uint triangleId = triangles.size();
                           edgeIdTriangles[usrcId].push_back(triangleId);
                           edgeIdTriangles[trguId].push_back(triangleId);
                           edgeIdTriangles[srctrgId].push_back(triangleId);
                         }
     });
    //mark srctrgid as processed
    processedEdges[srctrgId] = true;
    return edgeIdTriangles[srctrgId].size();
  }

  //implementation for saveTriangles == False
  template <>
  inline int EdgeSupportCentrality::compute_support<false>(node src, node trg) {
    int support = 0;
    G.forInNeighborsOf(src, [&](node v){
        if(G.hasEdge(trg, v))
           ++support;
      });
    return support;
  }

  
}





#endif
