#include "utils.h"

const char *int2str(int n)
{
    char buf[10];
    sprintf(buf, "%d", n);
    const char *s = buf;
    return s;
}

int str2int(const char *s)
{
    int n;
    n = atoi(s);
    return n;
}

bool equalString(const char *s1, const char *s2)
{
    if (strcmp(s1, s2) == 0)
        return true;
    else
        return false;
}
