#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

const float e = 2.718281;

int getConflictNum(int* seq) {

    int conflictNum = 0;
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 8; j++) {
            if (seq[i] == seq[j]) conflictNum++;
            int dx = i - j;
            int dy = seq[i] - seq[j];
            if ((dx == dy) || ((dx + dy) == 0)) conflictNum++;
        }
    return conflictNum;

}

int solution(int* seq, int& cost) {

    int nextConflictNum;
    int tempSeq[8];
    int flag = 0;
    int index = 0;
    int currentConflictNum = getConflictNum(seq);
    srand((unsigned int)time(NULL));

    while (currentConflictNum != 0) {
        int j;
        for (int i = 0; i < 8; i++)
            tempSeq[i] = seq[i];
        flag++;

        while (1) {
            index = (index + 1) % 8;
            for (j = 0; j < 8; j++) {
                if (j != tempSeq[index]) {
                    int improve;
                    tempSeq[index] = j;
                    nextConflictNum = getConflictNum(tempSeq);
                    improve = currentConflictNum - nextConflictNum;
                    if (improve > 0) {
                        cost++;
                        seq[index] = j;
                        currentConflictNum = nextConflictNum;
                        break;
                    } else if (improve < 0) {
                        float temp = rand() / (float)(RAND_MAX);
                        float pro = pow(e, (((float)improve) / ((float)currentConflictNum / 2.0)));
                        if (temp <= pro) {
                            cost++;
                            seq[index] = j;
                            currentConflictNum = nextConflictNum;
                            break;
                        }
                    }
                    tempSeq[index] = seq[index];
                }
            }
            if (j < 8) break;
        }
        if (flag > 100000000) break;
    }

}

int main() {

    clock_t start, finish;
    int successNum = 0;
    int successCost = 0;
    int failCost = 0;
    int seq[8];
    char buffer[20];
    char str[2];
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    start = clock();

    while (fin.getline(buffer, 20)) {
        int cost = 0;
        int result;
        for (int i = 0; i < 8; i++) {
            str[0] = buffer[i];
            str[1] = '\0';
            seq[i] = atoi(str);
        }
        result = solution(seq, cost);
        fout << "need steps: " << cost << ", result: ";
        if (result == 0) {
            successCost += cost;
            successNum++;
            fout << "success" << endl;
        } else {
            failCost += cost;
            fout << "fail" << endl;
        }
    }

    finish = clock();
    fout << "success number: " << successNum << ", ";
    if (successNum > 0) fout << "average success cost: " << (successCost / successNum) << ", ";
    if (successNum < 30) fout << "average fail cost: " << (failCost / (30 - successNum)) << ", ";
    fout << "need: " << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    return 0;

}

