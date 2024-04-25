#include <iostream>
#include "strategy.h"
#include <valarray>

namespace NAVIGATION
{
    void delay(const int& time)
    {
        clock_t now = clock();
        while ((clock() - now) < time)
        {
        ;
        }
        
    }

    Astar::Astar(const int& h_type_, const int& algo_type_) : h_type(h_type_), algo_type(algo_type_)
    {
    }

    bool Astar::search(const unique_ptr<GridMapBase>& map, vector<Node*>& result_nodes)
    {
        //initial start node
        open_queue.emplace(*map->start_node);   //put start node into open queue
        open_set.insert(map->start_node);       //put start node into hash table
        Node* current_node = map->start_node;   //set start node to current node

        //set move direction
        vector<pair<int, int>> move_step = 
        {
            pair<int, int>(0,1),
            pair<int, int>(0,-1),
            pair<int, int>(1,0),
            pair<int, int>(-1,0),
            pair<int, int>(-1,1),
            pair<int, int>(-1,-1),
            pair<int, int>(1,-1),
            pair<int, int>(1,1),
        };

        //search process
        while (!open_queue.empty())
        {
            // present node
            int r = open_queue.top().row;   //row number
            int c = open_queue.top().col;   //col number
            current_node = &map->grid_map[r][c];    //update current node to min f node
            std::cout << "current_node->f = " << current_node->f << ", current_node->r = " << r << ", current_node->c = " << c << std::endl;

            // draw close node
            setfillcolor(YELLOW);
            drawNodeStep(map->start_node, map->end_node, current_node, DELAYTIME_SEARCH);

            open_queue.pop();   // pop up current node
            open_set.erase(current_node);   // pop up current node
            close_set.insert(current_node); // push into close set

            // already reach the final node
            if (current_node == map->end_node)
            {
                final_length = current_node->g;

                while (current_node->parent_node)
                {
                    current_node->node_type = NodeType::result_way;
                    result_nodes.emplace_back(current_node);
                    current_node = current_node->parent_node;
                }
                reverse(result_nodes.begin(), result_nodes.end());
                std::cout << "Astar search successsfully!" << std::endl;

                //Show result
                printResult(result_nodes);
                map->printMap();
                drawResult(map->start_node, map->end_node, result_nodes);
                return true;
            }

            // normal search
            for (auto it = move_step.begin(); it != move_step.end(); it++)
            {
                Node node_tmp(r + it->first, c+ it->second);    //Get next node
                if (map->outOfMap(node_tmp))
                {
                    continue;
                }
                Node* next_node = &map->grid_map[node_tmp.row][node_tmp.col];
                // This node has been found in close table or next node is objects
                if (close_set.find(next_node) != close_set.end() || map->obs_nodes.find(next_node) != map->obs_nodes.end())
                {
                    continue;
                }

                // Get step length by direction
                step_len = abs(it->first) == abs(it->second) ? XLEN : LEN;
                if (open_set.find(next_node) != open_set.end())
                {
                    if (current_node->g + step_len < next_node->g)
                    {
                        calCost(*current_node, *next_node, *map->end_node);
                        next_node->parent_node = current_node;
                    }
                }
                else    // if not in open table, add to open table
                {
                    calCost(*current_node, *next_node, *map->end_node);
                    next_node->parent_node = current_node;

                    open_queue.emplace(*next_node);     // add to open table
                    open_set.insert(next_node);         // add to open table

                    // Draw open node
                    setfillcolor(LIGHTCYAN);
                    drawNodeStep(map->start_node, map->end_node, next_node, DELAYTIME_SEARCH);
                }
            }
        }

        //search fail
        std::cout << "Astar search fail!" << std::endl;
        drawResult(map->start_node, map->end_node, result_nodes);
        return false;
    }

    int Astar::heuristicDis(const Node& node1, const Node& node2)
    {
        if (h_type == HType::Euclidean)
        {
            return hypot(node1.col - node2.col, node1.row - node2.row) * LEN;
        }
        else if (h_type == HType::Manhattan)
        {
            return (abs(node1.col - node2.col) + abs(node1.row - node2.row)) * LEN;
        }
        else if(h_type == HType::Chebyshev)
        {
            int len_col = abs(node1.col - node2.col);
            int len_row = abs(node1.row - node2.row);
            int x_step = std::min(len_col, len_row);
            int res_step = abs(len_col - len_row);
            return x_step * XLEN + res_step * LEN;
        }
        else
        {

        }

        return 0;
    }

    void Astar::calCost(const Node& current_node, Node& next_node, const Node& end_node)
    {
        next_node.g = current_node.g + step_len;
        next_node.h = heuristicDis(next_node, end_node);

        if (algo_type == AlgoType::Dijkstra)
        {
            next_node.h = 0;
        }
        else if (algo_type == AlgoType::BFS)
        {
            next_node.g = 0;
        }

        next_node.f = next_node.g + next_node.h;
        std::cout << "f = " << next_node.f << ", g = " << next_node.g << ", h = " << next_node.h << std::endl;

    }

    void Astar::printResult(const vector<Node*>& result_nodes)
    {
        std::cout << "Path nodes number: " << result_nodes.size() << std::endl;
        std::cout << "Search nodes: " << close_set.size() << std::endl;
        std::cout << "Path length: " << final_length << std::endl;

        for (const auto& result_node : result_nodes)
        {
            std::cout << "(" << result_node->row << ", " << result_node->col << "), "
            << "f: " << result_node->f << ", "
            << "g: " << result_node->g << ", "
            << "h: " << result_node->h << std::endl;
        }
    }

    void Astar::drawNodeStep(Node* const start, Node* const end, Node* const node, const int& time)
    {
        if(start != node && end != node)
        {
            BeginBatchDraw();
            node->drawNode();
            delay(time);
            EndBatchDraw();
        }
    }

    void Astar::drawResult(Node* const start, Node* const end, const vector<Node*>& result_nodes)
    {
        setfillcolor(GREEN);
        for (const auto& result_node : result_nodes)
        {
            drawNodeStep(start, end, result_node, DELAYTIME_RESULT);
        }
    }
}
