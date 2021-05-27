#include "utils.h"

string int2str(int n)
{
    char buf[10];
    sprintf(buf, "%d", n);
    string s = buf;
    return s;
}

int str2int(string s)
{
    int n;
    n = atoi(s.c_str());
    return n;
}
