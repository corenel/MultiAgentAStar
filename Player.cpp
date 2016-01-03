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
    std::cout << "Directive In World Coordinate System: " << directiveInWCS() << std::endl;
    std::cout << "Directive In Robot Coordinate System: " << directiveInRCS() << std::endl;
}

bool Player::isEnd() {
    return Flag;
}

void Player::init(AStar &astar) {
    Paths = astar.search(X, Y, TargetX, TargetY);
    PathsIterator = Paths.begin();
}

std::string Player::directiveInWCS() {
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

std::string Player::directiveInRCS() {
    std::string directInWCS = directiveInWCS();
    std::string directInRCS = "";

    int angle = 0;
    for (int i = 0; i < directInWCS.size(); i++) {
        if (angle == 0) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "F"; break;
                case 'L': directInRCS += "RRF"; angle = 180; break;
                case 'U': directInRCS += "LF"; angle = 90; break;
                case 'D': directInRCS += "RF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 90) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "RF"; angle = 0; break;
                case 'L': directInRCS += "LF"; angle = 180; break;
                case 'U': directInRCS += "F"; break;
                case 'D': directInRCS += "RRF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 180) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "RRF"; angle = 0; break;
                case 'L': directInRCS += "F"; break;
                case 'U': directInRCS += "RF"; angle = 90; break;
                case 'D': directInRCS += "LF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 270) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "LF"; angle = 0; break;
                case 'L': directInRCS += "RF"; angle = 180; break;
                case 'U': directInRCS += "RRF"; angle = 90; break;
                case 'D': directInRCS += "F"; break;
                default: break;
            }
        }
    }
    return directInRCS;
}
