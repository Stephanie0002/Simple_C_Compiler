#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string int2str(int n);
int str2int(string str);

struct varNode
{
    string name;
    string type;
    int num = -1;
    bool use_address = false;
    string bool_string;
};

struct funcNode
{
    bool is_definied = false;
    string name;
    string return_type;
    vector<varNode> para_list;
};

struct arrayNode
{
    string name;
    string type;
    int num = -1;
};

class block
{
public:
    funcNode func;                           //  如果是函数，记录函数名
    bool is_func = false;                    //  记录是否是函数
    map<string, struct varNode> var_map;     //  变量的map
    map<string, struct arrayNode> array_map; //  数组的map
    string break_label_name;
    bool can_break = false;
};

#endif