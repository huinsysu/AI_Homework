#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main() {

    ofstream fout("input.txt");
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 8; j++) {
            int temp = rand() % 8;
            fout << temp;
        }
        fout << endl;
    }
    fout.close();
    return 0;

}
