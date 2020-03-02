#include <networkit/graph/Graph.hpp>
#include <networkit/io/EdgeListReader.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/graph/BFS.hpp>
//#include <boost/program_options.hpp>
#include "../include/decompositions/hDegreeCentrality.hpp"
#include "../include/decompositions/DistanceGeneralizedCoreDecomposition.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <fstream>
#include <iterator>


// namespace po = boost::program_options;

int main(int argc, char const *argv[])
{   

    NetworKit::Graph g;
    
    // po::positional_options_description pos_args;
    // pos_args.add("input", 1);
    // pos_args.add("output", 1);
    // po::variables_map vm;
    // po::store(po::command_line_parser(argc, argv).positional(pos_args).run(), vm);
    // po::notify(vm);
    //auto data = vm["dataset"].as<std::vector<std::string>>();
    //std::cout << data[0] << std::endl; 


    // std::cout << "Start Reading Graph" << std::endl;
    // NetworKit::EdgeListReader reader(' ', 1, "#", true, true);
    // NetworKit::Graph g =  reader.read(o.dataset);

    /**
    //std::unique_ptr<NetworKit::HDegreeCentrality> degg(new NetworKit::HDegreeCentrality(g, o.h));
    
    //start decomposition    
    std::unique_ptr<NetworKit::DistanceGeneralizedCoreDecomposition> 
        degg(new NetworKit::DistanceGeneralizedCoreDecomposition(g,o.h));
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    degg->run();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

    //write to file
    std::ofstream f;
    f.open(o.output_file);
    g.forNodes([&](NetworKit::node v){
        f << v << "," << degg->score(v) << std::endl;
    });
    f.close();
    //Compute average degree
    double deg = std::accumulate(degg->scores().begin(), degg->scores().end(), 0.0);
    std::cout << deg/g.numberOfNodes() << std::endl;

    //free memory
    degg.reset();
    */
    return 0;

}
