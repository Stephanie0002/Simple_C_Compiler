#include "hashSet.h"

myHashSet initHashSet(int size)
{
    myHashSet set = new hashSet_;
    if (set == nullptr)
    {
        fprintf(stderr, "Error [Senmantic] Allocate space failed when initiating hash set.\n");
        return nullptr;
    }
    set->size = size;
    set->buckets = new myBucket[size];
    for (int i = 0; i < size; i++)
    {
        set->buckets[i].symbol_list = nullptr;
    }
    return set;
}

bool insert(myHashSet set, mySymbol *symbol)
{
    unsigned int hash = calHash(symbol->name);
    mySymbolList *listhead = set->buckets[hash].symbol_list;
    if (listhead == nullptr)
    {
        listhead = new mySymbolList;
        listhead->symbol = symbol;
        listhead->next = nullptr;
        set->buckets[hash].symbol_list = listhead;
    }
    else
    {
        mySymbolList *p = listhead;
        for (; p->next != nullptr; p = p->next)
        {
            if (p->symbol->name == symbol->name)
            {
                return false;
            }
        }
        if (p->symbol->name == symbol->name)
        {
            return false;
        }
        mySymbolList *newSymbol = new mySymbolList;
        newSymbol->symbol = symbol;
        newSymbol->next = nullptr;
        p->next = newSymbol;
    }
    return true;
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