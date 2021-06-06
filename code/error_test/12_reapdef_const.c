const int b = 1;
const int f[2] = {1, 2};
int f1()
{
    const int b = 1;
    const int f[2] = {1, 2};
    const int b = 1;
    const int f[2] = {1, 2};
}
int main()
{
    const int b = 1;
    const int f[2] = {1, 2};
    const int b = 1;
    const int f[2] = {1, 2};
    if (1){
        const int b = 1;
        const int f[2] = {1, 2};
    }
    while (1){
        const int b = 1;
        const int f[2] = {1, 2};
    }
}

