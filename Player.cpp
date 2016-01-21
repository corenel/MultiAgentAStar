#include "Player.h"

Player::Player(int _x, int _y, int _TargetX, int _TargetY) {
    X = _x;
    Y = _y;
    TargetX = _TargetX;
    TargetY = _TargetY;
    Flag = false;
}

void Player::update(AStar &astar) {
    if (!Paths.empty() && !Flag)
    {
        if (PathsIterator != Paths.end())
        {
            int tx = (*PathsIterator).x;
            int ty = (*PathsIterator).y;

            if (!(astar.isBlock(tx, ty)))
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
//				astar.setMapData(X, Y, true);
                PathsIterator = Paths.begin();
                PathsIterator++;
                tx = (*PathsIterator).x;
                ty = (*PathsIterator).y;
                X = tx;
                Y = ty;
                astar.setMapData(X, Y, false);
                TotalPaths.push_back(*PathsIterator);
                PathsIterator++;
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
        Flag = true;
        // Paths = astar.search(X, Y, TargetX, TargetY);
        // PathsIterator = Paths.begin();
    }
}

void Player::print(AStar &astar) {
    for (std::list<Node>::iterator PathsIterator = TotalPaths.begin(); PathsIterator != TotalPaths.end(); ++PathsIterator)
    {
        std::cout << "(" << (*PathsIterator).x << "," << (*PathsIterator).y << ")\t";
    }
    std::cout << std::endl;
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
    astar.setMapData(X, Y, false);
    TotalPaths.push_back(*PathsIterator);
    PathsIterator++;
}

std::string Player::directiveInWCS() {
    std::string direct = "";
    int PrevX, PrevY;
    std::list<Node>::iterator PathsIterator = TotalPaths.begin();
    do {
        PrevX = (*PathsIterator).x;
        PrevY = (*PathsIterator).y;
        PathsIterator++;
        if ((TargetX == PrevX) && (TargetY == PrevY)) {
            break;
        }
        else if (((*PathsIterator).x == PrevX + 1) && ((*PathsIterator).y == PrevY)) {
            direct += "R";
        }
        else if (((*PathsIterator).x == PrevX - 1) && ((*PathsIterator).y == PrevY)) {
            direct += "L";
        }
        else if (((*PathsIterator).y == PrevY + 1) && ((*PathsIterator).x == PrevX)) {
            direct += "D";
        }
        else if (((*PathsIterator).y == PrevY - 1) && ((*PathsIterator).x == PrevX)) {
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
                case 'L': directInRCS += "B"; break;
                case 'U': directInRCS += "SLF"; angle = 90; break;
                case 'D': directInRCS += "SRF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 90) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "SRF"; angle = 0; break;
                case 'L': directInRCS += "SLF"; angle = 180; break;
                case 'U': directInRCS += "F"; break;
                case 'D': directInRCS += "B"; break;
                default: break;
            }
        }
        else if (angle == 180) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "B"; break;
                case 'L': directInRCS += "F"; break;
                case 'U': directInRCS += "SRF"; angle = 90; break;
                case 'D': directInRCS += "SLF"; angle = 270; break;
                default: break;
            }
        }
        else if (angle == 270) {
            switch (directInWCS[i]) {
                case 'R': directInRCS += "SLF"; angle = 0; break;
                case 'L': directInRCS += "SRF"; angle = 180; break;
                case 'U': directInRCS += "B"; break;
                case 'D': directInRCS += "F"; break;
                default: break;
            }
        }
    }
    directInRCS += "G";
    return directInRCS;
}
