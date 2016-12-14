#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define SAMPLE_NUM 100000000

int sample_matrix[SAMPLE_NUM][5];

void generate_sample(int* sample_row) {

    int randB = rand() % 1000;
    int randE = rand() % 1000;
    sample_row[0] = randB < 1 ? 1 : 0;
    sample_row[1] = randE < 2 ? 1 : 0;

    int randA, randJ, randM;
    randA = rand() % 1000;
    if (sample_row[0] == 1 && sample_row[1] == 1) {
        sample_row[2] = randA < 950 ? 1 : 0;
    } else if (sample_row[0] == 1 && sample_row[1] == 0) {
        sample_row[2] = randA < 940 ? 1 : 0;
    } else if (sample_row[0] == 0 && sample_row[1] == 1) {
        sample_row[2] = randA < 290 ? 1 : 0;
    } else {
        sample_row[2] = randA < 1 ? 1 : 0;
    }
    randJ = rand() % 100;
    randM = rand() % 100;
    if (sample_row[2] == 1) {
        sample_row[3] = randJ < 90 ? 1 : 0;
        sample_row[4] = randM < 70 ? 1 : 0;
    } else {
        sample_row[3] = randJ < 5 ? 1 : 0;
        sample_row[4] = randM < 1 ? 1 : 0;
    }

}

int main() {

    int sample_num = SAMPLE_NUM;
    int observe_sample_num = 0;
    int query_sample_num = 0;
    srand(time(NULL));

    for (int i = 0; i < sample_num; i++) {
        generate_sample(sample_matrix[i]);
    }

    for (int i = 0 ; i < sample_num; i++) {
        if (sample_matrix[i][3] == 1 && sample_matrix[i][4] == 1) {
            observe_sample_num++;
            if (sample_matrix[i][0] == 1) {
                query_sample_num++;
            }
        }
    }
    double rate;
    rate = double(query_sample_num)/observe_sample_num;
    cout << "取样" << sample_num << "个，计算出P(b | j, m)为：" << rate << endl;

}
