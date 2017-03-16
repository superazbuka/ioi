
#include <iostream>

using namespace std;

const long long INF = 1234567890;

long long a[55][55];
long long d[55][55][55][55];
long long p[55][55];

long long sum(long long i, long long j, long long k, long long s)
{
    return p[i][j] - (k > 0 ? p[k - 1][j] : 0) - (s > 0 ? p[i][s - 1] : 0) + (k > 0 and s > 0 ? p[k - 1][s - 1] : 0);
}

long long den(long long i, long long j, long long k, long long s)
{
    if (d[i][j][k][s] != INF)
    {
        return d[i][j][k][s];
    }
    for (long long ni = i; ni < k; ni++)
    {
        d[i][j][k][s] = min(d[i][j][k][s], den(i, j, ni, s) + den(ni + 1, j, k, s));
    }
    for (long long nj = j; nj < s; nj++)
    {
        d[i][j][k][s] = min(d[i][j][k][s], den(i, j, k, nj) + den(i, nj + 1, k, s));
    }
    d[i][j][k][s] += sum(k, s, i, j);
    return d[i][j][k][s];
}

int main()
{
    long long n, m;
    cin >> n >> m;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < m; j++)
        {
            cin >> a[i][j];
            p[i][j] = (i > 0 ? p[i - 1][j] : 0) + (j > 0 ? p[i][j - 1] : 0) - (i > 0 and j > 0 ? p[i - 1][j - 1] : 0) + a[i][j];
        }
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < m; j++)
            for (long long k = 0; k < n; k++)
                for (long long s = 0; s < m; s++)
                {
                    if (i == k and j == s)
                        d[i][j][k][s] = 0;
                    else
                        d[i][j][k][s] = INF;
                }
    cout << den(0, 0, n - 1, m - 1) << endl;
    return 0;
}
