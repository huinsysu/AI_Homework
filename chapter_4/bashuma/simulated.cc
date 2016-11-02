#include "mainFunction.cc"

const float e = 2.718281;

int solution(int* seq, int& cost) {

    int improve, currentDistance;
    int tempSeq[9];
    int nextDistance = getDistance(seq);
    srand((unsigned int)time(NULL));

    while (nextDistance != 0) {
        currentDistance = nextDistance;
        cost++;
        for (int i = 0; i < 9; i++)
            tempSeq[i] = seq[i];

        for (int i = 0; i < 4; i++) {
            if (findNextSeq(tempSeq, i)) {
                nextDistance = getDistance(tempSeq);
                improve = currentDistance - nextDistance;
                if (improve > 0) {
                    for (int j = 0; j < 9; j++)
                        seq[j] = tempSeq[j];
                    break;
                } else if (improve < 0) {
                    float temp = rand() / (float)(RAND_MAX);
                    float pro = pow(e, (((float)improve) / ((float)currentDistance / 6.0)));
                    if (temp <= pro) {
                        for (int j = 0; j < 9; j++)
                            seq[j] = tempSeq[j];
                        break;
                    }
                } else {
                    float temp = rand() / (float)(RAND_MAX);
                    if (temp < 0.2) {
                        for (int j = 0; j < 9; j++)
                            seq[j] = tempSeq[j];
                        break;
                    }
                }
                for (int j = 0; j < 9; j++)
                    tempSeq[j] = seq[j];
                nextDistance = currentDistance;
            }
        }
        if (cost > 10000000) break;
    }
    return nextDistance;
}

int main() {

    clock_t start, finish;
    int successNum = 0;
    int failSteps = 0;
    int successSteps = 0;
    int seq[9];
    char str[2];
    char buffer[20];

    ifstream fin("input.txt");
    ofstream fout("output2.txt");
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

        fout <<  "need steps: " << cost << ", result: ";
        if (result == 0) {
            successSteps += cost;
            successNum++;
            fout << "success!" << endl;
        } else {
           failSteps += cost;
           fout << "fail!" << endl;
        }
    }

    finish = clock();
    fout << "success number: " << successNum << ", average success steps: " << (successSteps / successNum);
    if (successNum < 30) fout << ", average fail steps: " << (failSteps / (30 - successNum));
    fout << ", need " << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;

    fin.close();
    fout.close();
    return 0;

}

