#include <stdlib.h>
#include "AStar.h"

Node::Node(int _x, int _y) {
    x = _x;
    y = _y;
    parent = NULL;
    g = 0;
    h = 0;
    f = 0;
}

AStar::AStar(void)
{
    sStartNode = new Node(0, 0);
    sEndNode = new Node(0, 0);
    pcurrNode = NULL;
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWeight; j++) {
            setMapData(i, j, true);
        }
    }
}
AStar::~AStar(void)
{
    delete sStartNode;
    delete sEndNode;
    delete pcurrNode;
}
std::list<Node> AStar::search(int _x, int _y, int _TargetX, int _TargetY)
{
    setStartNode(_x, _y);
    setEndNode(_TargetX, _TargetY);

    Node *currentNode;
    currentNode = sStartNode;
    currentNode->parent = NULL;
    currentNode->g = 0;
    computeH(currentNode);
    computeF(currentNode);

    OpenList.clear();
    ClosedList.clear();

    pcurrNode = NULL;

    OpenList.push_front(sStartNode);
    do
    {
        currentNode = findBestNode();
        addNearbyNode(currentNode);

        ClosedList.push_front(currentNode);
        if (OpenList.size() < 1 || pcurrNode) break;
    } while (true);

    sEndNode->parent = currentNode;
    currentNode = sEndNode;
    std::list<Node> path;

    do
    {
        path.push_front(*currentNode);
//        std::cout << currentNode->x << "\t" <<currentNode->y << std::endl;
        if(currentNode->x == sStartNode->x && currentNode->y == sStartNode->y) break;
        currentNode = currentNode->parent;

    } while (true);

    return path;
}

bool AStar::isPath(std::list<Node> *path, int i, int j)
{
    for(std::list<Node>::iterator openIterator = path->begin(); openIterator != path->end(); ++openIterator)
    {
        if((*openIterator).x == i && (*openIterator).y == j) {
            return true;
        }
    }
    return false;
}

void AStar::addNearbyNode(Node *src){
    getNodeByPoint(src, src->x, src->y + 1);
    getNodeByPoint(src, src->x, src->y - 1);
    getNodeByPoint(src, src->x - 1, src->y);
    getNodeByPoint(src, src->x + 1, src->y);
}

void AStar::getNodeByPoint(Node *pareNode, int _x, int _y)
{
    if(!isValid(_x, _y))
        return;

    Node *sNode = new Node(_x, _y);
    if(isInClosedList(sNode) || isBlock(_x, _y))
    {
        return;
    }
    else
    {
        sNode->parent = pareNode;
        computeG(sNode);
        computeH(sNode);
        computeF(sNode);
        OpenList.push_front(sNode);
        if(sNode->x == sEndNode->x && sNode->y == sEndNode->y)
            pcurrNode = sNode;
    }
}

bool AStar::isInClosedList(Node *src)
{
    for(std::list<Node*>::iterator openIterator = ClosedList.begin(); openIterator != ClosedList.end(); ++openIterator)
    {
        if((*openIterator)->x == src->x && (*openIterator)->y == src->y){return true;}
    }
    return false;
}

bool AStar::isInOpenList(Node *src)
{
    for(std::list<Node*>::iterator openIterator = OpenList.begin(); openIterator != OpenList.end(); ++openIterator)
    {
        if((*openIterator)->x == src->x && (*openIterator)->y == src->y){return true;}
    }
    return false;
}

bool AStar::isBlock(int _x, int _y)
{
    if (isValid(_x, _y))
        return !MapData[_x][_y];
    return false;
}

void AStar::computeH(Node *node)
{
    node->h = (abs(node->x - sEndNode->x) + abs(node->y - sEndNode->y)) * SPEND_H;
}

void AStar::computeG(Node *node)
{
    if(node->x != node->parent->x && node->y != node->parent->y)
        node->g = node->parent->g + SPEND_G_FAR;
    else
        node->g = node->parent->g + SPEND_G_NEAR;
}

void AStar::computeF(Node *node)
{
    node->f = node->g + node->h;
}

Node* AStar::findBestNode()
{
    Node* bNode;
    int bestF = 9999999;
    std::list<Node*>::iterator iterT;
    for(std::list<Node*>::iterator openIterator = OpenList.begin(); openIterator != OpenList.end(); ++openIterator)
    {
        if(bestF > (*openIterator)->f){
            bestF = (*openIterator)->f; bNode = *openIterator;
            iterT = openIterator;
        }
    }
    if(bNode)
        OpenList.erase(iterT);
    return bNode;
}

void AStar::setMapData(int _x, int _y, bool _data) {
    if (isValid(_x, _y))
        MapData[_x][_y] = _data;
}

bool AStar::isValid(int _x, int _y) {
    if (_x >= 0 && _x < MapWeight && _y >= 0 && _y < MapHeight)
        return true;
    else {
        return false;
    }
}

void AStar::drawMap(std::list<Node> path) {
    for(int j=0;j<MapWeight;++j)
    {
        for (int i=0;i<MapHeight;++i)
        {
            if(isPath(&path, i, j))
                std::cout<<"〇"<<"\t";
            else if (isBlock(i, j))
                std::cout<<"■"<<"\t";
            else
                std::cout<<"×"<<"\t";
        }
        std::cout << std::endl;
    }
}
