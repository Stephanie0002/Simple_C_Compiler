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

char *charUp(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }
    }
    return str;
}
