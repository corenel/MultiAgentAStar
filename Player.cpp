#include "Player.h"

Player::Player(int _x, int _y, int _TargetX, int _TargetY){
    X = _x;
    Y = _y;
    TargetX = _TargetX;
    TargetY = _TargetY;
    Flag = false;
}

void Player::update(AStar &astar){
    if (!Paths.empty())
    {
        if (PathsIterator != Paths.end())
        {
            // PathsIterator++;
            int tx = (*PathsIterator).x;
            int ty = (*PathsIterator).y;
            // PathsIterator--;

            if (!astar.isBlock(tx, ty))
            {
                astar.setMapData(X, Y, true);
                X = tx;
                Y = ty;
                astar.setMapData(X, Y, false);
                TotalPaths.push_back(*PathsIterator);
                PathsIterator++;
            }
            else
            {
                astar.setMapData(X, Y, true);
                Paths = astar.search(X, Y, TargetX, TargetY);
                PathsIterator = Paths.begin();
            }
        }
        else
        {
            astar.setMapData(X, Y, false);
            Paths.clear();
            PathsIterator = Paths.begin();
            Flag = true;
        }
    }
    else
    {
        Paths = astar.search(X, Y, TargetX, TargetY);
        PathsIterator = Paths.begin();
    }
}

void Player::print(AStar &astar) {
    for(std::list<Node>::iterator PathsIterator = TotalPaths.begin(); PathsIterator != TotalPaths.end(); ++PathsIterator)
    {
        std::cout << (*PathsIterator).x << "\t" << (*PathsIterator).y << std::endl;
    }
    astar.drawMap(TotalPaths);
    std::cout << "Directive: " << directive() << std::endl;
}

bool Player::isEnd() {
    return Flag;
}

void Player::init(AStar &astar) {
    Paths = astar.search(X, Y, TargetX, TargetY);
    PathsIterator = Paths.begin();
}

std::string Player::directive() {
    std::string direct = "";
    int PrevX, PrevY;
    std::list<Node>::iterator PathsIterator = TotalPaths.begin();
    do {
        PrevX = (*PathsIterator).x;
        PrevY = (*PathsIterator).y;
        *PathsIterator++;
        if ((*PathsIterator).x == PrevX + 1) {
            direct += "R";
        }
        else if ((*PathsIterator).x == PrevX - 1) {
            direct += "L";
        }
        else if ((*PathsIterator).y == PrevY + 1) {
            direct += "D";
        }
        else if ((*PathsIterator).y == PrevY - 1) {
            direct += "U";
        }
    } while (PathsIterator != TotalPaths.end());

    return direct;
}
