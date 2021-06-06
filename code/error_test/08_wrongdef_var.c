int main()
{
    int b = 2;
    int c = 3;
    int f[2] = {};
    int g[2] = {1};
    int h[2] = {1, 2, 3};
    int j[b] = {1};
    int k[b] = {1, 2};
    int l[2] = {1, 2};
    int m[l] = {1, 2};
    int o[2] = l;
    int j[l[5]] = {1, 2, 3};
    int p[2] = {l[1], 2};
}