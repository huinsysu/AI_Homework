#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int goal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {

    int index;
    int seq[9];
    ofstream fout("input.txt");

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 9; j++)
            seq[j] = goal[j];
        index = 0;
        for (int j = 0; j < 2000; j++) {
            int random = rand()%16;
            int dir;
            if (random < 4) dir = 0;
            else if (random < 8) dir = 1;
            else if (random < 12) dir = 2;
            else if (random < 16) dir = 3;
            int newx = index % 3 + dx[dir];
            int newy = index / 3 + dy[dir];

            if (newx >= 0 && newx <= 2 && newy >= 0 && newy <= 2) {
                int newindex = newx + newy * 3;
                int moveNum = seq[newindex];
                seq[newindex] = 0;
                seq[index] = moveNum;
                index = newindex;
            }
        }
        for (int j = 0; j < 9; j++)
            fout << seq[j] << " ";
        fout << endl;
    }

    fout.close();
    return 0;

}
