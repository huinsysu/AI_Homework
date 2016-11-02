#include "mainFunction.cc"

int solution(int* seq, int& cost) {

    int tempSeq[9];
    int nextDistance = getDistance(seq);
    int currentDistance = 45;

    while (nextDistance < currentDistance) {
        currentDistance = nextDistance;
        cost++;
        for (int i = 0; i < 9; i++)
            tempSeq[i] = seq[i];

        for (int i = 0; i < 4; i++) {
            if (findNextSeq(tempSeq, i)) {
                nextDistance = getDistance(tempSeq);
            
                if (nextDistance < currentDistance) {
                    for (int j = 0; j < 9; j++)
                        seq[j] = tempSeq[j];
                    break;
                }
                for (int j = 0; j < 9; j++)
                    tempSeq[j] = seq[j];
            }
        }
    }
    return currentDistance;

}

int main() {

    clock_t start, finish;
    int successSteps = 0;
    int failSteps = 0;
    int successNum = 0;
    int seq[9];
    char str[2];
    char buffer[20];

    ifstream fin("input.txt");
    ofstream fout("output0.txt");

    start = clock();

    while (fin.getline(buffer, 20)) {
        int cost = 0;
        int result;
        for (int i = 0; i < 9; i++) {
            str[0] = buffer[2 * i];
            str[1] = '\0';
            seq[i] = atoi(str);
        }
        result = solution(seq, cost);

        fout << "need steps: " << cost << ", " << "result: ";
        if (result == 0) {
            successNum++;
            successSteps += cost;
            fout << "success!" << endl;
        } else {
            failSteps += cost;
            fout << "fail!" << endl;
        }
    }

    finish = clock();

    fout << "success number: " << successNum << ", ";
    if (successNum > 0) fout << "average success steps: " << (successSteps / successNum) << ", ";
    fout << "average fail steps: " << (failSteps / (30 - successNum)) << ", need ";
    fout << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;

    fin.close();
    fout.close();

    return 0;

}

