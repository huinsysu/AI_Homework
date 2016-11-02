#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

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

    int currentConflictNum = 30;
    int nextConflictNum = getConflictNum(seq);
    int tempSeq[8];
    int index = 0;
    while (nextConflictNum < currentConflictNum) {
        int j;
        currentConflictNum = nextConflictNum;
        for (int i = 0; i < 8; i++)
            tempSeq[i] = seq[i];

        for (int i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                if (j != seq[index]) {
                    tempSeq[index] = j;
                    nextConflictNum = getConflictNum(tempSeq);
                    if (nextConflictNum < currentConflictNum) {
                        seq[index] = j;
                        cost++;
                        break;
                    }
                    tempSeq[index] = seq[index];
                }
            }
            index = (index + 1) % 8;
            if (j < 8) break;
        }
    }
    return currentConflictNum;

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
    ofstream fout("output0.txt");
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
    fout << "average fail cost: " << (failCost / (30 - successNum)) << ", need: ";
    fout << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    fin.close();
    fout.close();

    return 0;

}

