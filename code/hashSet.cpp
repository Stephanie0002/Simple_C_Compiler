#include "hashSet.h"

myHashSet initHashSet(int size)
{
    myHashSet set = new hashSet_;
    if (set == NULL)
    {
        fprintf(stderr, "Error [Senmantic] Allocate space failed when initiating hash set.\n");
        return NULL;
    }
    set->size = size;
    set->buckets = new myBucket[size];
    for (int i = 0; i < size; i++)
    {
        set->buckets[i].symbol_list = NULL;
    }
    return set;
}

bool contains(myHashSet set, string name, mySymbolType type)
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
            if (p->symbol->name == name)
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
        listhead = new mySymbolList;
        listhead->symbol = symbol;
        listhead->next = NULL;
        set->buckets[hash].symbol_list = listhead;
    }
    else
    {
        mySymbolList *p = listhead;
        for (; p->next != NULL; p = p->next)
        {
            if (p->symbol->name == symbol->name && p->symbol->symbol_type == symbol->symbol_type)
            {
                fprintf(stderr, "ERROR [Semantic] Symbol is already in the symbol table.\n");
            }
        }
        if (p->symbol->name == symbol->name && p->symbol->symbol_type == symbol->symbol_type)
        {
            fprintf(stderr, "ERROR [Semantic] Symbol is already in the symbol table.\n");
        }
        mySymbolList *newSymbol = new mySymbolList;
        newSymbol->symbol = symbol;
        newSymbol->next = NULL;
        p->next = newSymbol;
    }
}

mySymbol *get(myHashSet set, string name, mySymbolType type)
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
            if (p->symbol->name == name && p->symbol->symbol_type == type)
            {
                return p->symbol;
            }
        }
        return NULL;
    }
}

unsigned int calHash(string name)
{
    unsigned int val = 0, tmp;
    for (int i = 0; i < name.length(); i++)
    {
        val = (val << 2) + name.at(i);
        if (tmp = val & ~(HASH_SIZE - 1))
            val = (val ^ (tmp >> 12)) & (HASH_SIZE - 1);
    }
    return val;
}