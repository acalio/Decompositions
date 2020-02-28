#ifndef HDEGREE_CENTRALITY_HPP_
#define HDEGREE_CENTRALITY_HPP_

#include <networkit/centrality/DegreeCentrality.hpp>
#include <unordered_set>


namespace NetworKit {

class HDegreeCentrality: public DegreeCentrality {
public:
    HDegreeCentrality(const Graph& G, int h_=1, bool save_reachable_set = false, bool normalized = false, bool outDeg = false, bool ignoreSelfLoop= false);

    void run() override;

    std::unordered_set<node> &getReachSet(node v);

    std::vector<std::unordered_set<node>> &getReachSets();


protected:

    void assureReachSet();

    int h;
    bool save_reachable_set;
    std::vector<std::unordered_set<node>> reach_set; 
};
}
#endif // NETWORKIT_CENTRALITY_DEGREE_CENTRALITY_HPP_
