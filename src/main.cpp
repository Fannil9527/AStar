#include <iostream>
#include "main.h"
using namespace NAVIGATION;

int main()
{
    //Initial easyX, and create graph window and command window
    initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);

    Node start_node(6, 5, NodeType::start);
    Node end_node(28, 40, NodeType::end);
    unique_ptr<GridMapBase> grid_map_dir = make_unique<GridMap>(start_node, end_node);  //with smart pointer
    
    system("pause");
    
    //Close the graph window
    closegraph();
    return 0;
}