#include "utils.h"
#include <cstdlib>

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

bool equalString(const char *s1, const char *s2)
{
    if (strcmp(s1, s2) == 0)
        return true;
    else
        return false;
}
