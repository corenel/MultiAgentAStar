#include <iostream>
#include "AStar.h"
#include "Player.h"
using namespace std;

int main() {
    AStar astar;
    Player AGV[3] = { Player(1, 4, 2, 1) , Player(2, 0, 3, 4), Player(2, 2, 2, 2)};

    // Set obstacles
//    for (int i = 2; i < 8; i+=3){
//        for (int j = 2; j < 8; j++) {
//            astar.setMapData(i, j, false);
//        }
//    }
    astar.setMapData(1, 1, false);
    astar.setMapData(2, 2, false);
    astar.setMapData(4, 2, false);
    astar.setMapData(2, 3, false);

    // Initialize paths
    for (int i = 0; i < 3; i++) {
        AGV[i].init(astar);
    }

    // Plan paths with collision avoidance
    while (!(AGV[0].isEnd() && AGV[1].isEnd() && AGV[2].isEnd())){
        for (int i = 0; i < 3; i++) {
            AGV[i].update(astar);
        }
    }

    // Print paths
    for (int i = 0; i < 3; i++) {
        AGV[i].print(astar);
    }
    return 0;
}