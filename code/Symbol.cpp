#include "Symbol.h"

mySymbol *createSymbol(string name, mySymbolType type)
{
    mySymbol *symbol = new mySymbol;
    symbol->name = name;
    symbol->symbol_type = type;
    switch (type)
    {
    case VAR:
    case FUNC:
        symbol->func = new myFunc;
        break;
    default:
        fprintf(stderr, "ERROR [Semantic] Wrong symbol type when creating symbol.\n");
        return NULL;
    }
    return symbol;
}

void printDataType(myData *data)
{
    if (data == NULL)
    {
        printf("(null)\n");
        return;
    }
    string data_type[] = {"BASIC", "ARRAY"};
    printf("\tdata type: %s\n", data_type[data->data_type].c_str());
    printf("\tdata is r value: %s\n", data->is_r_value ? "yes" : "no");
    if (data->data_type == BASIC)
    {
        string basic_type[] = {"INT", "FLOAT", "BOOL"};
        printf("\tbasic: %s\n", basic_type[data->basic].c_str());
    }
    else if (data->data_type == ARRAY)
    {
        printf("\tarray size: %d\n", data->array.size);
        printf("\tarray data type: %s\n", data_type[data->array.elem->data_type].c_str());
        printDataType(data->array.elem);
    }
    else
    {
        fprintf(stderr, "ERROR [Semantic] Wrong data type when printing.\n");
    }
}