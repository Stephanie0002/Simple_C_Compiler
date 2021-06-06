#ifndef __SYMBOL__
#define __SYMBOL__

#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

typedef struct Data_ myData;
typedef struct Symbol_ mySymbol;
typedef struct Param_ myParam;
typedef struct Func_ myFunc;
typedef struct SymbolList_ mySymbolList;

typedef enum DataType_
{
    BASIC,
    ARRAY,
} myDataType;
typedef enum BasicType_
{
    INT,
} myBasicType;
struct Data_
{
    myDataType data_type;
    bool is_r_value;
    union
    {
        myBasicType basic; // 基本类型
        struct
        {
            myData *elem;
            int size;
        } array; // 数组类型
    };
    int value;
};

typedef enum SymbolType_
{
    VAR,
    FUNC,
    CONST
} mySymbolType;
struct Symbol_
{
    string name;
    mySymbolType symbol_type;
    union
    {
        myData *type;
        myFunc *func;
    };
};

struct Param_
{
    myData *type;  // 参数的类型
    myParam *next; // 下一个参数
    string para_name;
};

struct Func_
{
    myData *ret_type;
    int param_num;
    myParam *param_list; // 函数参数列表
};

struct SymbolList_
{
    mySymbol *symbol;
    mySymbolList *next;
};

mySymbol *createSymbol(string name, mySymbolType type);
void printDataType(myData *data);

#endif