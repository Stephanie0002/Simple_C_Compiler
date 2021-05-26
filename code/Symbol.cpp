#include "Symbol.h"

mySymbol *createSymbol(const char *name, mySymbolType type)
{
    mySymbol *symbol = (mySymbol *)malloc(sizeof(mySymbol));

    symbol->name = name;
    symbol->symbol_type = type;

    switch (type)
    {
    case VAR:
    case FUNC:
        symbol->func = (myFunc *)malloc(sizeof(myFunc));
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
    const char *data_type[] = {"BASIC", "ARRAY"};
    printf("data type: %s\n", data_type[data->data_type]);
    printf("data is r value: %s\n", data->is_r_value ? "yes" : "no");
    if (data->data_type == BASIC)
    {
        const char *basic_type[] = {"INT", "FLOAT"};
        printf("basic: %s\n", basic_type[data->basic]);
    }
    else if (data->data_type == ARRAY)
    {
        printf("array size: %d\n", data->array.size);
        printf("array data type: %s\n", data_type[data->array.elem->data_type]);
        printDataType(data->array.elem);
    }
    else
    {
        fprintf(stderr, "ERROR [Semantic] Wrong data type when printing.\n");
    }
}