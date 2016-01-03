#ifndef MULTIAGENTASTAR_PLAYER_H
#define MULTIAGENTASTAR_PLAYER_H
#include "AStar.h"
#include <string>

class Player {
public:
    int ID;
    int X; // current X
    int Y; // current Y
    int TargetX;
    int TargetY;
    std::list<Node> Paths;
    std::list<Node>::iterator PathsIterator;
    std::list<Node> TotalPaths;
    bool Flag;

    Player(int _x, int _y, int _TargetX, int _TargetY);
    void init(AStar &astar);
    void update(AStar &astar);
    void print(AStar &astar);
    std::string directive();
    bool isEnd();

};


#endif //MULTIAGENTASTAR_PLAYER_H
