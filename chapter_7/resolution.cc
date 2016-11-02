#include <iostream>
#include <string>
#include <string.h>
#include <map>

using namespace std;

typedef map<string, int> map_item;
typedef map<int, int> clause_content;
typedef struct KB_item{

    clause_content content;
    clause_content::iterator point;

}KB;
int map_index = 0;

void deal_clause(map_item &item, KB &clause, char *buf) {

    int index = 0;
    char str[20];

    for (int i = 0; i <= strlen(buf); i++) {
        if (buf[i] == '\0' || buf[i] == '|' ) {
            str[index] = '\0';
            if (str[0] != '!') {
                map_item::iterator it = item.find(str);
                if (it == item.end())
                    item[str] = map_index++;
                clause.content[item[str]] = 1;
            } else {
                for (int j = 0; j < strlen(str); j++)
                    str[j] = str[j+1];
                map_item::iterator it = item.find(str);
                if (it == item.end())
                    item[str] = map_index++;
                clause.content[item[str]] = 0;
            }
            index = 0;
            if (buf[i] == '\0')
                clause.point = clause.content.begin();
        } else {
            str[index++] = buf[i];
        }
   }

}

int main() {

    map_item item;
    KB clauses[100];
    int clause_num = 0;
    char buf[20];
    char query_str[20];


    cout << "请输入规则，Q表示输入结束。" << endl;

    while (cin >> buf) {
       if (buf[0] == 'Q')
           break;
       deal_clause(item, clauses[clause_num], buf);
       clause_num++;
    }

    cout << "请输入要查询的项。" << endl;

    cin >> query_str;
    for (int i = strlen(query_str) + 1; i > 0; i--)
        query_str[i] = query_str[i-1];
    query_str[0] = '!';

    deal_clause(item, clauses[clause_num], query_str);
    clause_num++;

    while (1) {
        for (int i = 0; i < clause_num - 1; i++) {
            for (int j = i + 1; j < clause_num; j++) {
                while (clauses[i].point != clauses[i].content.end()) {
                    if (clauses[j].content.find(clauses[i].point->first) != clauses[j].content.end())
                       if (clauses[j].content[clauses[i].point->first] != clauses[i].point->second) {
                           
                       }
                }
            }
        }
    }

    return 0;
}
