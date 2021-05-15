int fact(int n)
{
    int temp;
    if (n == 1)
        return n;
    else
    {
        temp = (n * fact(n - 1));
        return temp;
    }
}

int main()
{
    int result, times;
    times = read();
    int i = 0;
    while (i < times)
    {
        int m = read();
        if (m > 1)
        {
            result = fact(m);
        }
        else
        {
            result = 1;
        }
        print(result);
        i = i + 1;
    }
    return 0;
}