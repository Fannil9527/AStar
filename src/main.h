#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#include "strategy.h"
#include "config.h"
#include <graphics.h>

namespace NAVIGATION
{
    class Navigator
    {
    public:
        Navigator();
        bool process(const int& h_type_, const int& algo_type_);
    
    public:
        vector<Node*> result_nodes;
        unique_ptr<GridMapBase> grid_map_ptr;
        unique_ptr<StrategyBase> strategy_ptr;
    };
}

#endif