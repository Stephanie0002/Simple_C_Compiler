int main()
{
    int a;
    int b = 1;
    int c[2] = {1, 2};

    // Array can not be LVal
    c = 1;
    c = a;
    c = b;

    // Array can not in cal
    a = b + c;
    a = b - c;
    a = b / c;
    a = b * c;
    a = b % c;

    a = 1 + c;
    a = 1 - c;
    a = 1 / c;
    a = 1 * c;
    a = 1 % c;

    // Const value
    const int o = 1;
    o = 5;
    a = o;

    // Complex exp
    a = c[((b * 1 / 2) + 4 + (a - b) - (b + 3) % 2) % c];

    // Redudand operator
    a = +-b + 1;
    a = --1;

    // Compare
    int m;
    int n[2];
    if (m + a - 1 + 1 - 1 + 1 * 1 / 1 % 1 == n)
    {
        return 0;
    }
    if (m + 1 != n)
    {
        return 0;
    }
}