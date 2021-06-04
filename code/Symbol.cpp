#include "Symbol.h"

mySymbol *createSymbol(string name, mySymbolType type)
{
    mySymbol *symbol = new mySymbol;
    symbol->name = name;
    symbol->symbol_type = type;
    switch (type)
    {
    case VAR:
    case CONST:
    case FUNC:
        symbol->func = new myFunc;
        break;

    default:
        fprintf(stderr, "ERROR [Semantic] Wrong symbol type when creating symbol.\n");
        return nullptr;
    }
    return symbol;
}

void printDataType(myData *data)
{
    if (data == nullptr)
    {
        return;
    }
    string data_type[] = {"BASIC", "ARRAY"};
    printf("\tdata type: %s\n", data_type[data->data_type].c_str());
    printf("\tdata is r value: %s\n", data->is_r_value ? "yes" : "no");
    if (data->data_type == BASIC)
    {
        string basic_type[] = {"INT"};
        printf("\tbasic: %s\n", basic_type[data->basic].c_str());
        printf("\tvalue: %d\n", data->value);
    }
    else if (data->data_type == ARRAY)
    {
        printf("\t\tarray size: %d\n", data->array.size);
        printf("\t\tarray data type: %s\n", data_type[data->data_type].c_str());
        printf("\t\tarray data value: %d\n", data->value);
        printDataType(data->array.elem);
    }
    else
    {
        fprintf(stderr, "ERROR [Semantic] Wrong data type when printing.\n");
    }
}