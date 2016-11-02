#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <queue>

using namespace std;

typedef struct KB_clause {

    int conclusion;
    int premise_num;
    int premise_arr[20];
    int flag;
    int fact;

}KB;

typedef map<string, int> map_item;
typedef queue<int> que;
int map_index = 0;

void deal_clause(map_item &item, KB &clause, que &agenda, char *buf) {

    int index = 0;
    char str[10];

    for (int i = 0; i <= strlen(buf); i++) {
        if (buf[i] == '\0') {
            str[index] = '\0';
            map_item::iterator it = item.find(str);
            if (it == item.end())
                item[str] = map_index++;
            if (clause.flag == 0) {
                clause.fact = item[str];
                agenda.push(item[str]);
            } else {
                clause.conclusion = item[str];
            }
        } else if (buf[i] == '&' || buf[i] == '>') {
            str[index] = '\0';
            map_item::iterator it = item.find(str);
            if (it == item.end())
                item[str] = map_index++;
            clause.premise_arr[clause.premise_num++] = item[str];
            clause.flag = 1;
            index = 0;
        } else {
            str[index++] = buf[i];
        }
    }

}

void init_clause(KB *clauses) {

    for (int i = 0; i < 100; i++) {
        clauses[i].flag = 0;
        clauses[i].premise_num = 0;
    }

}

int main() {

    char buf[20];
    char query_str[20];
    map_item item;
    que agenda;
    KB clauses[100];
    int result = 0;
    int clause_num = 0;
    int symbol_num;
    int count[100];
    int inferred[100];

    init_clause(clauses);

    cout << "请输入Horn子句。" << endl;

    while (cin >> buf) {
        if (buf[0] == 'q')
            break;
        deal_clause(item, clauses[clause_num], agenda, buf);
        clause_num++;
    }

    symbol_num = item.size();
    for (int i = 0; i < symbol_num; i++)
        inferred[i] = 0;
    for (int i = 0; i < clause_num; i++)
        count[i] = clauses[i].premise_num;

    cout << "请输入要查询的结论。" << endl;

    cin >> query_str;

    while (!agenda.empty()) {
        int top = agenda.front();
        agenda.pop();
        if (top == item[query_str]) {
            result = 1;
            break;
        }
        if (inferred[top] == 0) {
            inferred[top] = 1;
            for (int i = 0; i < clause_num; i++) {
                for (int j = 0; j < clauses[i].premise_num; j++) {
                    if (clauses[i].premise_arr[j] == top) {
                        count[i]--;
                        if (count[i] == 0)
                            agenda.push(clauses[i].conclusion);
                    }
                }
            }
        }
    }
    if (result == 1)
        cout << "知识库可以推出该结论。" << endl;
    else
        cout << "知识不能推出该结论。" << endl;

    return 0;
}




