
#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <chrono>
#include <string>
#include <fstream>
#include <networkit/graph/Graph.hpp>
#include <type_traits>
#include "../include/decompositions/EdgeSupportCentrality.hpp"
#include "../include/decompositions/TrussDecomposition.hpp"


namespace Utility {

bool isEdgeBased(NetworKit::Centrality *centralityMeasure){
  return dynamic_cast<NetworKit::EdgeSupportCentrality*>(centralityMeasure)!=0 ||
      dynamic_cast<NetworKit::TrussDecomposition*>(centralityMeasure)!=0;
}

template <class F>
int timed_run(F &&f){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //call the function
    f();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
}

void _saveResult(const NetworKit::Graph& G,
                 NetworKit::Centrality& centralityMeasure,
                 std::string output_path){
  std::ofstream f;
  f.open(output_path);
  G.forEdges([&](NetworKit::node u, NetworKit::node v, NetworKit::edgeweight ew, NetworKit::edgeid eid){
               f << u << "," << v << "," << centralityMeasure.score(eid) << "\n";
             });
  f.close();
}

template <typename C,
          typename =
          std::enable_if<std::is_base_of<NetworKit::Centrality, C>::value>
          >
void saveResult(const NetworKit::Graph& G,
                C& centralityMeasure,
                std::string output_path) {

  if(isEdgeBased(&centralityMeasure)){
    _saveResult(G, centralityMeasure, output_path);
    return;
  }

  std::ofstream f;
  f.open(output_path);
  G.forNodes([&](NetworKit::node v){
               f << v << "," << centralityMeasure.score(v) << "\n";
             });
  f.close();
}



}
#endif 
