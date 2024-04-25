#include <iostream>
#include "main.h"
//using namespace NAVIGATION;

namespace NAVIGATION
{
    Navigator::Navigator()
    {
        Node start_node(6, 5, NodeType::start);
        Node end_node(28, 40, NodeType::end);
        grid_map_ptr = make_unique<GridMap>(start_node, end_node);  //with smart pointer
        system("pause");
    }

    bool Navigator::process(const int& h_type_, const int& algo_type_)
    {
        strategy_ptr = make_unique<Astar>(h_type_, algo_type_);
        return strategy_ptr->search(grid_map_ptr, result_nodes);
    }
}

int main()
{
    //Initial easyX, and create graph window and command window
    initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);

    unique_ptr<NAVIGATION::Navigator> navigator_ptr = make_unique<NAVIGATION::Navigator>(); 
    if (navigator_ptr->process(NAVIGATION::HType::Manhattan, NAVIGATION::AlgoType::BFS))
    {
        std::cout << "Finish!" << std::endl;
    }
    
    std::cin.get();
    system("pause");
    
    //Close the graph window
    closegraph();
    return 0;
}