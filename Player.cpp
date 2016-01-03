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
    std::cout << "Directive In World Axis: " << directiveInWorldAxis() << std::endl;
    std::cout << "Directive In Robot Axis: " << directiveInRobotAxis() << std::endl;
}

bool Player::isEnd() {
    return Flag;
}

void Player::init(AStar &astar) {
    Paths = astar.search(X, Y, TargetX, TargetY);
    PathsIterator = Paths.begin();
}

std::string Player::directiveInWorldAxis() {
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

std::string Player::directiveInRobotAxis() {
    std::string directInWorldAxis = directiveInWorldAxis();
    std::string direct = "";

    int angle = 0;
    for (int i = 0; i < directInWorldAxis.size(); i++) {
        if (angle == 0) {
            switch (directInWorldAxis[i]) {
                case 'R': direct += "F"; break;
                case 'L': direct += "RRF"; angle = 180; break;
                case 'U': direct += "LF"; angle = 90; break;
                case 'D': direct += "RF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 90) {
            switch (directInWorldAxis[i]) {
                case 'R': direct += "RF"; angle = 0; break;
                case 'L': direct += "LF"; angle = 180; break;
                case 'U': direct += "F"; break;
                case 'D': direct += "RRF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 180) {
            switch (directInWorldAxis[i]) {
                case 'R': direct += "RRF"; angle = 0; break;
                case 'L': direct += "F"; break;
                case 'U': direct += "RF"; angle = 90; break;
                case 'D': direct += "LF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 270) {
            switch (directInWorldAxis[i]) {
                case 'R': direct += "LF"; angle = 0; break;
                case 'L': direct += "RF"; angle = 180; break;
                case 'U': direct += "RRF"; angle = 90; break;
                case 'D': direct += "F"; break;
                default: break;
            }
        }
    }
    return direct;
}
