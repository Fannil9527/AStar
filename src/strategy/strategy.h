#pragma once
#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <iostream>
#include <cmath>
#include "grad_map.h"
#include <queue>

using std::priority_queue, std::pair;

namespace NAVIGATION
{
    enum HType
    {
        Euclidean,      //Eular distance
        Manhattan,      //
        Chebyshev
    };

    enum AlgoType
    {
        Dijkstra,
        BFS,
        AStar
    };

    class StrategyBase
    {
    public:
        virtual bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) = 0;   // search process
    };

    class Astar : public StrategyBase
    {
    public:
        Astar(const int& h_type_, const int& algo_type_);
        bool search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes) override;
        int heuristicDis(const Node& node1, const Node& node2);
        void calCost(const Node& current_node, Node& next_node, const Node& end_node);
        void printResult(const vector<Node*>& result_nodes);
        void drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time);
        void drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes);

    public:
        priority_queue<Node> open_queue;    // open table, small top stack
        unordered_set<Node*> open_set;      // hash table
        unordered_set<Node*> close_set;     // hash table

        int h_type = HType::Manhattan;
        int algo_type = AlgoType::AStar;
        int final_length = 0;
        int step_len = 0;
    };
}

#endif