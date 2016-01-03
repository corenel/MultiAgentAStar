#ifndef MULTIAGENTASTAR_ASTAR_H
#define MULTIAGENTASTAR_ASTAR_H
#include <list>
#include <math.h>
#include <iostream>
#include <assert.h>

class Node
{
public:
    int x;
    int y;
    int f, g, h;
    struct Node *parent;
    Node(int _x, int _y);
};

class AStar{
public:
    static const int SPEND_H = 10;
    static const int SPEND_G_FAR = 14;
    static const int SPEND_G_NEAR = 10;
    std::list<Node*> OpenList;
    std::list<Node*> ClosedList;
    Node *sStartNode;
    Node *sEndNode;
    Node *pcurrNode;
    static const int MapHeight = 10;
    static const int MapWeight = 10;
    bool MapData[MapHeight][MapWeight];

    AStar(void);
    ~AStar(void);
    void setStartNode(int _x, int _y){ sStartNode->x = _x;sStartNode->y = _y;};
    void setEndNode(int _x, int _y){ sEndNode->x = _x;sEndNode->y = _y;};
    std::list<Node> search(int _x, int _y, int _TargetX, int _TargetY);
    void addNearbyNode(Node *src);
    void getNodeByPoint(Node *pareNode, int _x, int _y);
    bool isInClosedList(Node *src);
    bool isInOpenList(Node *src);
    bool isBlock(int _x, int _y);
    void computeH(Node *node);
    void computeG(Node *node);
    void computeF(Node *node);
    void setMapData(int _x, int _y, bool _data);
    Node*findBestNode();
    bool isPath(std::list<Node> *path, int i, int j);
    bool isValid(int _x, int _y);
    void drawMap(std::list<Node> path);
};


#endif //MULTIAGENTASTAR_ASTAR_H
