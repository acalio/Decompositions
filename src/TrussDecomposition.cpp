#include  "../include/decompositions/TrussDecomposition.hpp"
#include "../include/decompositions/EdgeSupportCentrality.hpp"
#include <vector>
#include <memory>

namespace NetworKit {

  TrussDecomposition::TrussDecomposition(const Graph &G):Centrality(G){}

  void TrussDecomposition::run() {
    if(!G.hasEdgeIds())
          throw std::runtime_error("Graph has not indexes! You must call indexEdges first");

    //initialize data structures
    index z = G.upperEdgeIdBound();
    std::vector<edgeid> queue(G.numberOfEdges());
    std::vector<index> edgePtr(z);
    std::vector<index> supportBegin(G.numberOfEdges());
    std::vector<count> support(z);
    std::vector<EdgeSupportCentrality::Triangle> triangles;
    std::vector<std::vector<int>> edgeIdTriangles;
    std::vector<bool> trianglePresence;
    
    /* Bucket sort by support */
    /* 1) bucket sizes */
    //Computeompan the support for each edge
    //    std::unique_ptr<EdgeSupportCentrality> esCentr = std::make_unique<EdgeSupportCentrality>(G,true);
    EdgeSupportCentrality es_centr(G,true);
    es_centr.run();
    G.forEdges([&](node u, node v, edgeweight ew, edgeid eid){
                 support[eid] = es_centr.score(static_cast<edgeid>(eid));
                 ++supportBegin[support[eid]];
               });

    triangles.swap(es_centr.triangles);
    edgeIdTriangles.swap(es_centr.edgeIdTriangles);
    trianglePresence.resize(edgeIdTriangles.size());
    trianglePresence.assign(trianglePresence.size(),true);

    //remove pointer
    //    esCentr.reset();

    index sum = 0; // in-place prefix sum
    for (index i = 0; i<supportBegin.size(); ++i) {
        index tmp = supportBegin[i];
        supportBegin[i] = sum;
        sum += tmp;
    }

    //sort eges/place in queue
    G.forEdges([&](node u, node v, edgeweight ew, edgeid eid){
                 count supp = support[eid];
                 index pos = supportBegin[supp];
                 ++supportBegin[supp];
                 queue[pos] = eid;
                 edgePtr[eid] = pos;
               });

    // 4 restore prefix sum
    index tmp = 0;
    for (index i=0; i<supportBegin.size(); ++i)
        std::swap(tmp, supportBegin[i]);

    /* start iteration */
    index trussIndex = 0;
    scoreData.clear();
    scoreData.resize(z);

    for (index i=0; i<G.numberOfEdges(); ++i) {
        edgeid e = queue[i];
        trussIndex = std::max(trussIndex, support[e]);

        scoreData[static_cast<node>(e)] = trussIndex + 2;

        /*
          Decease the support of each edges involved 
          in a triangle to which e belongs to
        */
        auto removeNeighborEdges =
            [&](edgeid ne){
                if (edgePtr[ne] <= i)
                    return;
                
                count oldSupport = support[ne];
                count newSupport = oldSupport -1;
                support[ne] = newSupport;

                if(supportBegin[oldSupport]<=i)
                    supportBegin[oldSupport] = i+1;

                if(supportBegin[newSupport]<=i)
                    supportBegin[newSupport] = i+1;

                //swap ne with the beginning of the current bucket
                index oldPos = edgePtr[ne];
                index newPos = supportBegin[oldSupport];
                edgeid edgeToSwap = queue[newPos];

                std::swap(queue[oldPos], queue[newPos]);
                std::swap(edgePtr[edgeToSwap], edgePtr[ne]);

                ++supportBegin[oldSupport];
            };

        //get all triangles e is involved in
        std::for_each(std::begin(edgeIdTriangles[e]),
                      std::end(edgeIdTriangles[e]),
                      [&](int tid) {
                          if(!trianglePresence[tid])
                              //this triangle has already been removed
                              return;
                          
                          EdgeSupportCentrality::Triangle& t = triangles[tid];
                          std::for_each(std::begin(t), std::end(t), removeNeighborEdges);
                          //mark the triangle as not present
                          trianglePresence[tid]=false;
                       });
        }

    hasRun = true;
  }

};


