#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define SAMPLE_NUM 1000000000

void weighted_sample(int* sample, double& w) {

    int randB = rand() % 1000;
    int randE = rand() % 1000;
    sample[0] = randB < 1 ? 1 : 0;
    sample[1] = randE < 2 ? 1 : 0;

    int randA, randJ, randM;
    randA = rand() % 1000;
    if (sample[0] == 1 && sample[1] == 1) {
        sample[2] = randA < 950 ? 1 : 0;
    } else if (sample[0] == 1 && sample[1] == 0) {
        sample[2] = randA < 940 ? 1 : 0;
    } else if (sample[0] == 0 && sample[1] == 1) {
        sample[2] = randA < 290 ? 1 : 0;
    } else {
        sample[2] = randA < 1 ? 1 : 0;
    }
    sample[3] = 1;
    sample[4] = 1;
    if (sample[2] == 1) w = 0.9 * 0.7;
    else w = 0.05 * 0.01;

}

int main() {

    int sample_num = SAMPLE_NUM;
    int sample_row[5];
    double W[2] = {0.0, 0.0};

    srand(time(NULL));
    for (int i = 0; i < sample_num; i++) {
        double w;
        weighted_sample(sample_row, w);
        if (sample_row[0] == 1) W[0] += w;
        else W[1] += w;
    }
    cout << "取样" << sample_num << "个，计算出P(b | j, m)为：" <<W[0]/(W[0] + W[1]) << endl;
    return 0;
}

