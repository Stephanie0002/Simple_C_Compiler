#include "hashSet.h"

myHashSet initHashSet(int size)
{
    myHashSet set = (myHashSet)malloc(sizeof(struct hashSet_));
    if (set == NULL)
        return NULL;
    set->size = size;
    set->buckets = (myBucket *)malloc(sizeof(Bucket_) * size);
    for (int i = 0; i < size; i++)
    {
        set->buckets[i].symbol_list = NULL;
    }
    return set;
}

bool contains(myHashSet set, const char *name, mySymbolType type)
{
    unsigned int hash = calHash(name);
    mySymbolList *listhead = set->buckets[hash].symbol_list;
    if (listhead == NULL)
    {
        return false;
    }
    else
    {
        for (mySymbolList *p = listhead; p != NULL; p = p->next)
        {
            if (strcmp(p->symbol->name, name) == 0)
            {
                mySymbolType p_type = p->symbol->symbol_type;
                switch (type)
                {
                case VAR:
                    if (p_type == VAR)
                        return true;
                    break;
                case FUNC:
                    if (p_type == FUNC)
                        return true;
                    break;
                default:
                    break;
                }
            }
        }
        return false;
    }
}

void insert(myHashSet set, mySymbol *symbol)
{
    unsigned int hash = calHash(symbol->name);
    mySymbolList *listhead = set->buckets[hash].symbol_list;
    if (listhead == NULL)
    {
        listhead = (mySymbolList *)malloc(sizeof(mySymbolList));
        listhead->symbol = symbol;
        listhead->next = NULL;
        set->buckets[hash].symbol_list = listhead;
    }
    else
    {
        mySymbolList *p = listhead;
        for (; p->next != NULL; p = p->next)
        {
            if (strcmp(p->symbol->name, symbol->name) == 0 && p->symbol->symbol_type == symbol->symbol_type)
            {
                fprintf(stderr, "ERROR [Semantic] Symbol is already in the symbol table.\n");
            }
        }
        if (strcmp(p->symbol->name, symbol->name) == 0 && p->symbol->symbol_type == symbol->symbol_type)
        {
            fprintf(stderr, "ERROR [Semantic] Symbol is already in the symbol table.\n");
        }
        mySymbolList *newSymbol = (mySymbolList *)malloc(sizeof(mySymbolList));
        newSymbol->symbol = symbol;
        newSymbol->next = NULL;
        p->next = newSymbol;
    }
}

mySymbol *get(myHashSet set, const char *name, mySymbolType type)
{
    unsigned int hash = calHash(name);
    mySymbolList *listhead = set->buckets[hash].symbol_list;
    if (listhead == NULL)
    {
        return NULL;
    }
    else
    {
        for (mySymbolList *p = listhead; p != NULL; p = p->next)
        {
            if (strcmp(p->symbol->name, name) == 0 && p->symbol->symbol_type == type)
            {
                return p->symbol;
            }
        }
        return NULL;
    }
}

unsigned int calHash(const char *name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~(HASH_SIZE - 1))
            val = (val ^ (i >> 12)) & (HASH_SIZE - 1);
    }
    return val;
}