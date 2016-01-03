#include <iostream>
#include "AStar.h"
#include "Player.h"
using namespace std;

int main() {
    AStar astar;
    Player agv1(0, 3, 8, 8), agv2(2, 5, 8, 5), agv3(0, 0, 2, 9), agv4(8, 8, 2, 2);
    agv1.init(astar);
    agv2.init(astar);
    agv3.init(astar);

    for (int i = 1; i < 9; i+=2){
        for (int j = 1; j < 9; j++) {
            astar.setMapData(i, j, false);
        }
    }

    while (!(agv1.isEnd() && agv2.isEnd() && agv3.isEnd() && agv4.isEnd())){
        agv1.update(astar);
        agv2.update(astar);
        agv3.update(astar);
        agv4.update(astar);
    }

    agv3.print(astar);

    // astar.drawMap(astar.search(0, 0, 9, 9));
    return 0;
}