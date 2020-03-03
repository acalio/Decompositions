#include <networkit/graph/Graph.hpp>
#include <networkit/io/EdgeListReader.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/graph/BFS.hpp>
#include <boost/program_options.hpp>
#include <networkit/centrality/CoreDecomposition.hpp>
#include "../include/decompositions/hDegreeCentrality.hpp"
#include "../include/decompositions/DistanceGeneralizedCoreDecomposition.hpp"
#include "../include/decompositions/KPeakDecomposition.hpp"
#include "../include/decompositions/NeighborCoreness.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>


namespace po = boost::program_options;



// Define custom validator for 
// specifying the algorithm from 
// command line
struct deco_algorithm {
public:
    deco_algorithm(const std::string &n): name(n){}
    std::string name;
};


//custom  validator for the algorithm field
void validate(boost::any& v, 
            const std::vector<std::string>& values, 
            deco_algorithm*, int){
    
    static std::vector<std::string> available_algorithms = {
        "kcore",
        "kpeak",
        "ktruss",
        "neighcoreness",
        "dgcore"
    };

    // Make sure no previous assignment to 'a' was made.
    po::validators::check_first_occurrence(v);

    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    std::string s = po::validators::get_single_string(values);

    // convert to lower case
    std::for_each(s.begin(), s.end(), [](char &c) {c = ::tolower(c);});
    
    //check if the given algo arg correspond to an available decomposition
    if(std::find(available_algorithms.begin(),
                 available_algorithms.end(),s)==available_algorithms.end())
            throw po::validation_error(po::validation_error::invalid_option_value); 

    v = boost::any(deco_algorithm(s));
}



int main(int argc, char const *argv[])
{   
    try{
        //program options
        po::options_description desc("Allowed Options");
        desc.add_options()
            ("help", "produce help message")
            ("input,in", po::value<std::string>(), "input graph")
            ("output,out", po::value<std::string>(), "ouput file")
            ("algorithm,a", po::value<deco_algorithm>(), 
            "decomposition algorithm. Available options: \n\t [*] kcore \n\t [*] kpeak \n\t [*] ktruss \n\t [*] neighcoreness \n\t [*] dgcore");

        // define positional arguments
        po::positional_options_description pos_args;
        pos_args.add("input", 1);
        pos_args.add("output", 1);
        pos_args.add("algorithm", 1);   

        //distance generalized core decomposition algorithm options
        po::options_description dgc_opt("Dist. Gen. Core Deco. options");
        dgc_opt.add_options()("distance,h", po::value<int>()->default_value(1), "neighborhood distance");

        //neighbor coreness decomposition algorithm options
        po::options_description neigh_opt("Neighbor Coreness Deco. options");
        neigh_opt.add_options()("depth,d", po::value<int>()->default_value(1), "neighbors depth");


        //graph input reader option
        po::options_description reader_options("Graph Reader Options");
        reader_options.add_options()
            ("first-node, fn", po::value<int>()->default_value(0), "first node index")
            ("separator, sep", po::value<char>()->default_value(' '), "separator");

        //add groups to the general options description
        desc.add(reader_options).add(dgc_opt).add(neigh_opt);

        // read command line arguments
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
            .options(desc)
            .positional(pos_args)
            .run(), vm);
        po::notify(vm);
        
        if(vm.count("help")){
            std::cout << desc << std::endl;
            return 0;
        }
        
        //read the input graph
        auto input_dataset = vm["input"].as<std::string>();
        auto first_node = vm["first-node"].as<int>();
        auto separator = vm["separator"].as<char>();

        std::cout << "Start Reading Graph" << std::endl;
        NetworKit::EdgeListReader reader(separator, first_node, "#", true, true);
        NetworKit::Graph g =  reader.read(input_dataset);
        std::cout << g.numberOfNodes() <<  " is Directed: "<< g.isDirected() <<std::endl;


        //create the algorithm 
        std::unique_ptr<NetworKit::Centrality> algo_ptr;
        auto deco_algo = vm["algorithm"].as<deco_algorithm>().name;
        if(deco_algo=="kcore"){
            algo_ptr = std::make_unique<NetworKit::CoreDecomposition>(g, false, true, false, NetworKit::CoreDecomposition::Direction::Out); 
        }else if (deco_algo=="dgcore"){
            int h = vm["distance"].as<int>();
            algo_ptr = std::make_unique<NetworKit::DistanceGeneralizedCoreDecomposition>(g, h);
        }else if (deco_algo=="kpeak"){
            algo_ptr = std::make_unique<NetworKit::KPeakDecomposition>(g); 
        }else if (deco_algo=="neighcoreness"){
            int depth = vm["depth"].as<int>();
            algo_ptr = std::make_unique<NetworKit::NeighborCoreness>(g, depth); 
        }

        //execute the algorithm
        int time = timed_run([&](){
            algo_ptr->run();
        });
        std::cout << "Time = " <<  time << "[s]" << std::endl;


        //save results to the output file
        std::string output_file = vm["output"].as<std::string>();
        std::ofstream f;
        f.open(output_file);
        g.forNodes([&](NetworKit::node v){
            f << v << "," << algo_ptr->score(v) << std::endl;
        });
        f.close();

        //free memory
        algo_ptr.reset();

    }catch(std::exception &e){
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
