#include "grad_map.h"

namespace NAVIGATION
{
    Node::Node(const int& r, const int& c, const int& type):row(r), col(c), node_type(type)
    {
    }

    void Node::drawNode() const // draw node
    {
        int left = ORIX + col * LEN;
        int right = left + LEN;
        int top = ORIY + row * LEN;
        int botton = top + LEN;
        fillrectangle(left, top, right, botton);
    }

    bool GridMapBase::outOfMap(const Node& node)
    {
        return (node.col < 0) || (node.col >= COLS) || (node.row < 0) || (node.row >= ROWS);
    }

    bool GridMapBase::GridMapInit(const Node& start, const Node& end)   // map initial, input start, end point
    {
        if(outOfMap(start) || outOfMap(end))
        {
           cout << "Start point or end point end of window's range." << endl;
           return false; 
        }

        // Create map
        for (int i = 0; i < ROWS; i++)  // Create col
        {
            vector<Node> row_tmp;   // Every row
            for (int j = 0; j < COLS; j++)  // Create row
            {
                Node node_tmp(i,j);
                row_tmp.emplace_back(node_tmp);
            }
            grid_map.emplace_back(row_tmp);
        }

        //update start and end point
        grid_map[start.row][start.col].node_type = NodeType::start;     // Update start point
        grid_map[end.row][end.col].node_type = NodeType::end;       // Update end point

        start_node = &grid_map[start.row][start.col];
        end_node = &grid_map[end.row][end.col];

        return true;
    }

    void GridMapBase::printMap()
    {
        cout << "Row number: " << ROWS << " Column number: " << COLS << endl;
        cout << "Start row number: " << start_node->row
            << ", Start column number: " << start_node->col
            << ", End row number: " << end_node->row
            << ", End column number: " << end_node->col << endl;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (grid_map[i][j].node_type == NodeType::normal)
                {
                    cout << "  ";
                }
                else
                {
                    cout << grid_map[i][j].node_type << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    GridMap::GridMap(const Node& start, const Node& end)
    {
        assert(GridMapInit(start, end));    // initial with assert, because it is in create function
        printMap();     // print
        drawMap();      // draw map
    }

    void GridMapBase::drawMap()
    {
        setbkcolor(WHITE);      // set color of back: white
        setlinecolor(BLACK);    // Set color of line: black
        setlinestyle(PS_SOLID, 2);  // Set type of line
        cleardevice();

        // Avoid flash in windows
        BeginBatchDraw();
        setfillcolor(WHITE);    // fullfill color with white
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j ++) // Draw each row
            {
                grid_map[i][j].drawNode();
            }
        }

        // Draw start and end point
        setfillcolor(RED);      // fulfill color with red
        start_node->drawNode();

        setfillcolor(BLUE);
        end_node->drawNode();

        setfillcolor(BROWN);
        for(const auto& obs_node : obs_nodes)   //scan node in vector
        {
            obs_node->drawNode();
        }

        EndBatchDraw();
    }

    void GridMap::addObs()
    {

    }
} // namespace 
