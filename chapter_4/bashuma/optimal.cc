#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <time.h>
using namespace std;

struct node {
  int seq[9];//节点的状态。
  int depth;//搜索的层数。
  int estimated_cost;//节点的预测代价。
  int total;//节点总代价。
  struct node* father_node;//当前节点的父节点。
};

list<struct node*> to_be_tested;//待扩展的节点链表。
list<struct node*> have_been_tested;//已经扩展的节点链表。
list<struct node*>::iterator point;

const int goal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};//目标节点的序列。
const int dx[] = {0, 0, 1, -1};//水平方向的移动。
const int dy[] = {1, -1, 0, 0};//竖直方向的移动。

int temp[9];//用于临时存放新生成节点的序列。

int test_mapping(struct node* N) {//检测是否到达目标状态。
    for (int i = 0; i < 9; i++)
        if (goal[i] != (N->seq)[i])
            return 0;
    return 1;
}

int find_blank(struct node *N) {//找到某个节点‘0’所在的位置。
    for (int i = 0; i < 9; i++)
        if ((N->seq)[i] == 0)
            return i;
}

int test_duplicating(int *arr){//检测某个状态是否已经在扩展的节点链表中。
    int flag = 0;
    for (point = have_been_tested.begin(); point != have_been_tested.end(); point++) {
        int i;
        for (i = 0; i < 9; i++)
            if (((*point)->seq)[i] != arr[i]) break;
        if (i == 9) flag = 1;
    }
    return flag == 1 ? 1 : 0;
}

int estimate_cost(int *seq) {//预测当前状态到达目标状态的开销。
 
    int counter = 0;
    
    for (int i = 0; i < 9; i++) {
        int currentx = i%3;
        int currenty = i/3;
        int targetx = seq[i]%3;
        int targety = seq[i]/3;
        counter += abs(currentx-targetx);
        counter += abs(currenty-targety);
    }
    return counter;

}

void add_to_list(struct node *N) {

    if (to_be_tested.empty()) {
        to_be_tested.push_front(N);
    } else {
        for (point = to_be_tested.begin(); point != to_be_tested.end(); point++)
            if (N->total <= (*point)->total) {
                to_be_tested.insert(point, N);
                break;
            }
        if (point == to_be_tested.end()) to_be_tested.push_back(N);
    }

}

struct node * solution(struct node *head) {

    to_be_tested.push_front(head);
    while (!to_be_tested.empty()) {
        struct node *top = to_be_tested.front();//链表头的节点。
        to_be_tested.pop_front();
        
        if (test_mapping(top)) return top;//匹配返回目标状态指针。
        
        int index = find_blank(top);   

        for (int i = 0; i < 4; i++) {
            int newx = index%3 + dx[i];
            int newy = index/3 + dy[i];

            if (newx >= 0 && newx <= 2 && newy >= 0 && newy <= 2) {
                int newindex = newx + newy*3;
                for (int j = 0; j < 9; j++)
                    temp[j] = (top->seq)[j];
                temp[index] = (top->seq)[newindex];
                temp[newindex] = 0;

                if (!test_duplicating(temp)) {
                    struct node *newNode = new struct node;
                    for (int k = 0; k < 9; k++)
                        (newNode->seq)[k] = temp[k];
                    newNode->father_node = top;
                    newNode->depth = top->depth + 1;
                    newNode->estimated_cost = estimate_cost(temp);
                    newNode->total = newNode->depth + newNode->estimated_cost;
                    add_to_list(newNode);
                }
            }
        }
        have_been_tested.push_front(top);
    }
    return NULL;//不匹配返回空指针。

}

int main() {
    
    clock_t start, finish;
    int successSteps = 0;
    char str[2];
    char buffer[20];    

    ifstream fin("input.txt");
    ofstream fout("output3.txt");
    start = clock();

    while (fin.getline(buffer, 20)) {
        int cost = 0;

        struct node *head = new struct node;
        head->estimated_cost = 0;
        head->depth = 0;
        head->father_node = NULL;
        for (int i = 0; i < 9; i++) {
            str[0] = buffer[2 * i];
            str[1] = '\0';
            (head->seq)[i] = atoi(str);
        }
        head->estimated_cost = estimate_cost(head->seq);
        head->total = head->estimated_cost + head->depth;
    
        struct node *target = solution(head);

        cost = target->depth;
        successSteps += cost;
 
        fout << "need steps: " << cost << ", result: success" << endl;

        for (point = to_be_tested.begin(); point != to_be_tested.end(); point++)
            delete *point;
        for (point = have_been_tested.begin(); point != have_been_tested.end(); point++)
            delete *point;
        to_be_tested.clear();
        have_been_tested.clear();
    }

    finish = clock();
    fout << "success number: 30, average success steps: " << (successSteps / 30);
    fout << ", need" << ((double)(finish - start) / CLOCKS_PER_SEC) << " seconds" << endl;
    fin.close();
    fout.close();

    return 0;

}

