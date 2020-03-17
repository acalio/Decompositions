#include "../include/decompositions/EdgeSupportCentrality.hpp"
#include <type_traits>


namespace NetworKit {

EdgeSupportCentrality::Triangle::Triangle(std::vector<edgeid>&& eids){
    std::sort(eids.begin(), eids.end());
    edges.swap(eids);
}

  bool EdgeSupportCentrality::Triangle::operator==(const Triangle &other) const {
    bool areEquals = true;
    for (int i=0; i<edges.size() && areEquals; ++i)
      areEquals = edges[i]==other.edges[i];

    return areEquals;
}

bool EdgeSupportCentrality::Triangle::operator!=(const Triangle &other) const {
    return !(operator==(other));
}

std::vector<edgeid>::iterator EdgeSupportCentrality::Triangle::begin() {
    return edges.begin();
}

std::vector<edgeid>::iterator EdgeSupportCentrality::Triangle::end() {
    return edges.end();
}
  
EdgeSupportCentrality::EdgeSupportCentrality(const Graph& G, bool save):Centrality(G), saveTriangles(save), currentSrc(-1){}
  

  void EdgeSupportCentrality::run() {
    //index the edges
    if(!G.hasEdgeIds())
      throw std::runtime_error("Graph has not indexes! You must call indexEdges first");
      
    index z = G.upperEdgeIdBound();
    edgeIdTriangles.resize(z);
    processedEdges.resize(z);
    scoreData.resize(z);
    
    //score data now sotres an edge-based value.
    //each position correspond to the id of a node 
    scoreData.resize(z);

    G.forEdges([&](node u, node v, edgeweight ew, edgeid eid){
             int supp = compute_support<true>(u,v);
             //save to vector
             edgeid uvid = G.edgeId(u, v);
             scoreData[static_cast<edgeid>(uvid)] = supp;
    });
    
    hasRun = true;
}

  

}

