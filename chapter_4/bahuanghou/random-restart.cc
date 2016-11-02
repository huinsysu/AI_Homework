#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void generateRandomSeq(int* seq) {

    srand((unsigned int)time(NULL));
    for (int i = 0; i < 8; i++)
        seq[i] = (rand() % 8);

}

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
    int minConflictNum = getConflictNum(seq);
    int tempSeq[8];
    int minx = 0;
    int miny = seq[0];

    while (minConflictNum < currentConflictNum) {
        int tempConflictNum;
        currentConflictNum = minConflictNum;

        for (int i = 0; i < 8; i++)
            tempSeq[i] = seq[i];

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (j != tempSeq[i]) {
                    tempSeq[i] = j;
                    tempConflictNum = getConflictNum(tempSeq);
                    if (tempConflictNum < minConflictNum) {
                        minConflictNum = tempConflictNum;
                        minx = i;
                        miny = j;
                    }
                    tempSeq[i] = seq[i];
                }
            }
        }
        seq[minx] = miny;
        cost++;
    }
    return currentConflictNum;

}

int main() {

    clock_t start, finish;
    int successCost = 0;
    int seq[8];
    char buffer[20];
    char str[2];
    ifstream fin("input.txt");
    ofstream fout("output1.txt");
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
        while (result != 0) {
            generateRandomSeq(seq);
            result = solution(seq, cost);
        }
        successCost += cost;
        fout << "need steps: " << cost << ", result: success" << endl;
    }
    finish = clock();
    fout << "success number: 30, average success cost: " << (successCost / 30) << ", needs: ";
    fout << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    fin.close();
    fout.close();
    return 0;

}

