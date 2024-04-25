#pragma once
#ifndef _GRAD_MAP_H_
#define _GRAD_MAP_H_
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <assert.h>
#include <unordered_set>
#include "config.h"
#include <graphics.h>

//using namespace std;
using std::cout, std::endl;
using std::vector, std::unordered_set, std::unique_ptr, std::make_unique;

namespace NAVIGATION
{
    // Define node type
    enum NodeType
    {
        normal,     // normal node
        start,      // start node
        end,        // end node
        obs,        // object node
        result_way, // path node
    };

    // Node class
    class Node
    {
    //Create
    public:
        Node() = default;
        Node(const int& r, const int& c, const int& type = NodeType::normal);   //Create with parameter
        void drawNode() const;     // Draw node

        bool operator<(const Node& other_node) const {return this->f > other_node.f;}
    
    public:
        int row = 0;    // row in the map
        int col = 0;    // cloumn in the map

        int f = 0;      // Total cost for the node
        int g = 0;      // Cost from start point to the node
        int h = 0;      // Cost from the node to the end node

        int node_type = NodeType::normal;   // Initial node type
        Node* parent_node = nullptr;        // parent node of the end point
     
    };

    class GridMapBase       // Parent class of grad map
    {
    public:
        bool GridMapInit(const Node& start, const Node& end);   // Initial map information
        void printMap();    // print map in command window
        void drawMap();     // print map in graph window
        bool outOfMap(const Node& node);    // if node is out of window's range
        virtual void addObs() = 0;     // add ojbects

    public:
        vector<vector<Node>> grid_map;  // structure of map, two dimenson matrix
        Node* start_node = nullptr;     // Start point
        Node* end_node = nullptr;       // End point
        unordered_set<Node*> obs_nodes; // Obj node with hash table
    };

    // Could be extend with other type
    class GridMap : public GridMapBase  // Grad map
    {
    public:
        GridMap(const Node& start, const Node& end);    // Initial map information
        void addObs() override; // add objects
    };
}// end of namespace

#endif

