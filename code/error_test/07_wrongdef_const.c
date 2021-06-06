int main()
{
    int b = 2;
    const int c = 3;
    const int f[2] = {};
    const int g[2] = {1};
    const int h[2] = {1, 2, 3};
    const int j[b] = {1};
    const int k[b] = {1, 2};
    const int l[2] = {1, 2};
    const int m[l] = {1, 2};
    const int n = l;
    const int o[2] = l;
    const int j[l[5]] = {1, 2, 3};
    const int p[2] = {l[1], 2};
}