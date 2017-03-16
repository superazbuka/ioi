#include <iostream>

using namespace std;

long long a[2005][2005];
long long cnt[2005];
pair<long long, pair<long long, long long> > yc[2005];

int main()
{
    long long n, k, num;
    cin >> n >> k >> num;
    num--;
    for (int i = 0; i < k; i++)
        cnt[i] = 0;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < k; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 0)
                cnt[j]++;
        }
    for (long long i = 0; i < n; i++)
    {
        long long sum = 0, cnto = 0;
        for (long long j = 0; j < k; j++)
            if (a[i][j] == 1)
                sum += cnt[j], cnto++;
        yc[i] = {sum, {cnto, -i}};
    }
    long long ans = 0;
    for (long long i = 0; i < n; i++)
        if (yc[num] < yc[i])
            ans++;
    cout << yc[num].first << " " << ans + 1 << endl;
}

