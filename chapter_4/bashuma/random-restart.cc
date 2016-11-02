#include "mainFunction.cc"

int solution(int* seq, int& cost) {

    int tempSeq[9];
    int minDistance = 45;
    int minflag = -1;
    int nextDistance = getDistance(seq);

    while (nextDistance < minDistance) {
        minDistance = nextDistance;
        cost++;
        for (int i = 0; i < 9; i++)
            tempSeq[i] = seq[i];

        for (int i = 0; i < 4; i++) {
            if (findNextSeq(tempSeq, i)) {
                nextDistance = getDistance(tempSeq);
            
                if (nextDistance < minDistance)
                    minflag = i;

                for (int j = 0; j < 9; j++)
                    tempSeq[j] = seq[j];
            }
        }
        if (minflag >= 0)
            findNextSeq(seq, minflag);
    }
    return minDistance;

}

void getRandomSeq(int* seq) {

    int tempIndex;
    int constant[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 0; i < 9; i++) {
        do {
            tempIndex = rand() % 9;
        } while (constant[tempIndex] == -1);
        seq[i] = constant[tempIndex];
        constant[tempIndex] = -1;
    }

}

int main() {

    clock_t start, finish;
    int result;
    int successSteps = 0;
    int seq[9];
    char str[2];
    char buffer[20];
    srand((unsigned int)time(NULL));

    ifstream fin("input.txt");
    ofstream fout("output1.txt");
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
        while (result != 0) {
            getRandomSeq(seq);
            result = solution(seq, cost);
        }
        successSteps += cost;

        fout << "need steps: " << cost << ", result: " << "success!" <<endl;
    }
    finish = clock();
    fout << "success number: " << "30, average success steps: " << (successSteps / 30);
    fout << "need " << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    fin.close();
    fout.close();

    return 0;

}

