//采用曼哈顿距离作为目标函数。

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

const int dx[] = {0, 1, 0, -1};  //水平方向的移动。
const int dy[] = {1, 0, -1, 0};  //竖直方向的移动。


int findBlank(int* seq) {

    for (int i = 0; i < 9; i++)
        if (seq[i] == 0)
            return i;

}

int getDistance(int* seq) {

    int counter = 0;
    for (int i = 0; i < 9; i++) {
        int currentx = i % 3;
        int currenty = i / 3;
        int targetx = seq[i] % 3;
        int targety = seq[i] / 3;
        counter += abs(currentx - targetx);
        counter += abs(currenty - targety);
    }
    return counter;

}

int findNextSeq(int* seq, int flag) {

    int index = findBlank(seq);
    int newx = index % 3 + dx[flag];
    int newy = index / 3 + dy[flag];

    if (newx >= 0 && newx <= 2 && newy >= 0 && newy <= 2) {
        int newindex = newx + newy * 3;
        int tempNum = seq[newindex];
        seq[newindex] = 0;
        seq[index] = tempNum;
        return 1;
    } else {
        return 0;
    }

}

