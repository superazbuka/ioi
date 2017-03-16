#include <iostream>
#include <set>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

int tar[100];
int mass[2000];
set<int> a;
queue<int> b;
map<int, int> mp;
int ans = 0;

void req()
{
    while(!a.empty() and !b.empty())
    {
        mp[b.front()] = *a.begin();
        //cout << "! " << b.front() << " " << *a.begin() << endl;
        ans += mass[b.front()] * tar[*a.begin()];
        b.pop();
        a.erase(a.begin());
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> tar[i];
        a.insert(i);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> mass[i];
    }
    for (int io = 0; io < 2 * m; io++)
    {
        int x;
        cin >> x;
        int rx = x;
        x = abs(x) / x * (abs(x) - 1);
        if (rx < 0)
        {
            int tec = mp[-x];
            a.insert(tec);
        }
        else
        {
            b.push(x);
        }
        req();
    }
    cout << ans << endl;
}
