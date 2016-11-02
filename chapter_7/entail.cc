#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

int map_index = 0;

typedef map<string, int> map_item;
typedef struct logic_sentance {

    int master_symbol;
    bool true_false;
    int flag;
    int entail_symbol[20];
    int arr_len;

}base;

typedef struct query_item{

    int item_index;
    int flag;

}query;

void init_sentences(base* sentences) {

    for (int i = 0; i < 50; i++) {
        sentences[i].flag = 0;
        sentences[i].arr_len = 0;
        sentences[i].true_false = false;
    }

}

void deal_sentence(map_item &item, base &sentence, char* buf) {

    int index = 0;
    char str[10];
    for (int i = 0; i <= strlen(buf); i++) {
        if (buf[i] == '\0') {
            if (sentence.flag == 0) {
                str[index] = '\0';
                if (str[0] != '!') {
                    map_item::iterator it = item.find(str);
                    if (it == item.end())
                        item[str] = map_index++;
                    sentence.true_false = true;
                } else {
                    for (int k = 0; k < strlen(str); k++)
                        str[k] = str[k+1];
                    map_item::iterator it = item.find(str);
                    if (it == item.end())
                        item[str] = map_index++;
                    sentence.true_false = false;
                }
                sentence.master_symbol = item[str];
            } else {
                str[index] = '\0';
                map_item::iterator it = item.find(str);
                if (it == item.end())
                    item[str] = map_index++;
                sentence.entail_symbol[sentence.arr_len++] = item[str];
            }
        } else if (buf[i] == '=') {
            str[index] = '\0';
            if (str[0] != '!') {
                map_item::iterator it = item.find(str);
                if (it == item.end())
                    item[str] = map_index++;
                sentence.true_false = true;
            } else {
                for (int k = 0; k < strlen(str); k++)
                     str[k] = str[k+1];
                map_item::iterator it = item.find(str);
                if (it == item.end())
                    item[str] = map_index++;
                sentence.true_false = false;
            }
            sentence.master_symbol = item[str];
            sentence.flag = 1;

            index = 0;
        } else if (buf[i] == '|') {
            str[index] = '\0';
            map_item::iterator it = item.find(str);
            if (it == item.end())
                item[str] = map_index++;
            sentence.entail_symbol[sentence.arr_len++] = item[str];

            index = 0;
        } else {
            str[index++] = buf[i];
        }
    }

}

void deal_query_str(map_item &item, query &qitem, char *buf) {

    char str[10];
    int index = 0;
    for (int i = 0; i <= strlen(buf); i++) {
        if (buf[i] == '\0') {
            str[index] = '\0';
            if (buf[0] != '!') {
                qitem.item_index = item[str];
                qitem.flag = 1;
            } else {
                for (int j = 0; j < strlen(str); j++)
                    str[j] = str[j + 1];
                qitem.item_index = item[str];
                qitem.flag = 0;
            }
        } else {
            str[index++] = buf[i];
        }
    }

}

void check_by_case(map_item &item, base *sentences, int sentence_num, int *row, query &qitem, int &result) {

    int i;
    for (i = 0; i < sentence_num; i++) {
        if (sentences[i].flag == 0) {
            if (row[sentences[i].master_symbol] != sentences[i].true_false) break;
        } else {
            int j;
            for (j = 0; j < sentences[i].arr_len; j++)
                if (row[sentences[i].entail_symbol[j]] == 1) break;
            if (row[sentences[i].master_symbol] == 1) {
                if (j == sentences[i].arr_len) break;
            } else {
                if (j < sentences[i].arr_len) break;
            }
        }
    }
    if (i == sentence_num) {
        if (row[qitem.item_index] == qitem.flag)
           result = 1;
    }

}

int main() {

    char buf[20];
    char query_str[20];
    map_item item;
    base sentences[50];
    int sentence_num = 0;
    int table[2048][11];

    init_sentences(sentences);

    cout << "请依次输入知识库，输入Q表示结束。" << endl;

    while (cin >> buf) {
        if (buf[0] == 'Q')
            break;
        deal_sentence(item, sentences[sentence_num], buf);
        sentence_num++;
    }

    cout << "请输入要验证的句子，输入Q表示输入结束。" << endl;

    while (cin >> query_str) {

        if (query_str[0] == 'Q')
            break;

        query qitem;

        deal_query_str(item, qitem, query_str);

        for (int i = 0; i < 11; i++)
            for (int j = 0; j < 2048; j++)
                table[i][j] = 0;

        int result = 0;
        int symbol_num = item.size();
        int case_num = pow(2, symbol_num);

        for (int i = 0; i < case_num; i++) {
            int temp = i;
            int col_index = symbol_num - 1;
            while (temp / 2 != 0) {
                table[i][col_index--] = temp % 2;
                temp = temp / 2;
            }
            table[i][col_index] = i == 0 ? 0 : 1;

            check_by_case(item, sentences, sentence_num, table[i], qitem, result);
            if (result) break;
        }
        if (result) {
            cout << "该句子成立。" << endl;
        } else {
            cout << "该句子不成立。" << endl;
        }
    }

    return 0;
}


