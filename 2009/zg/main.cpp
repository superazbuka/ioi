#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int> > g;
vector<pair<int, int> > sob[25000];
int clrs[200000];
int timer = 0;
int all[200010];
map<pair<int, int>, int> pans;
int cnt[25000];

void dfs(int v)
{
    sob[clrs[v]].push_back({timer, v + 1});
    //cout << clrs[v] << " ";
    timer++;
    for (int i = 0; i < g[v].size(); i++)
    {
        dfs(g[v][i]);
    }
    sob[clrs[v]].push_back({timer, -v - 1});
    //cout << -clrs[v] << " ";
    timer++;
}

int giveans(int x, int y)
{
    int si = sob[x].size();
        int tec = 0;
        int ans = 0;
        for (int i = 0; i < si; i++)
        {
            while(tec < sob[y].size() and sob[y][tec] < sob[x][i])
                tec++;
                //cout << tec << endl;
            if (sob[x][i].second > 0)
            {
                all[sob[x][i].second] = tec;
            }
            else
            {
                ans += tec - all[-sob[x][i].second];
            }
        }
        return ans / 2 ;
}

int main()
{
    int n, r, q;
    cin >> n >> r >> q;
    int x;
    cin >> x;
    clrs[0] = x - 1;
    cnt[x - 1]++;
    g.resize(n);
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        g[x - 1].push_back(i);
        clrs[i] = y - 1;
        cnt[y - 1]++;
    }
    dfs(0);
    //cout << endld;
    for (int io  = 0; io < q; io++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (pans.find({x, y}) == pans.end())
            pans[{x, y}] = giveans(x, y);
        cout << pans[{x, y}] << endl;
    }
}
