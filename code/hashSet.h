#ifndef __HASHSET__
#define __HASHSET__

#include <cstdio>
#include <cstdlib>
#include <string>
#include "Symbol.h"

using namespace std;

#define HASH_SIZE 16384

typedef struct hashSet_ *myHashSet;

typedef struct Bucket_
{
    mySymbolList *symbol_list;
} myBucket;

struct hashSet_
{
    int size;
    myBucket *buckets;
};

myHashSet initHashSet(int size);
bool contains(myHashSet set, string name, mySymbolType type);
void insert(myHashSet set, mySymbol *symbol);
unsigned int calHash(string name);
mySymbol *get(myHashSet set, string name, mySymbolType type);

#endif