#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 1000;
const int INF = 1234567890;

int n, s;

char fld[MAXN][MAXN];
int br[MAXN][MAXN];
int tr[MAXN][MAXN];

int tx[] = {1, 0, -1, 0};
int ty[] = {0, 1, 0, -1};

int fx = 0;
int fy = 0;

pair<int, int> go(pair<int, int> my, int i)
{
    return {my.first + tx[i], my.second + ty[i]};
}

bool chesk(pair<int, int> next)
{
    if (next.first < 0 or next.first > n or next.second < 0 or next.second > n)
        return false;
    return true;
}

void rast()
{
    queue<pair<int, int> > a;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            br[i][j] = INF;
            if (fld[i][j] == 'H')
            {
                a.push({i, j});
                br[i][j] = 0;
            }
        }
    while(!a.empty())
    {
        pair<int, int> next = a.front();
        a.pop();
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> ne = go(next, i);
            if (chesk(ne) and (fld[ne.first][ne.second] == 'G' or fld[ne.first][ne.second] == 'M') and br[ne.first][ne.second] > br[next.first][next.second] + 1)
            {
                a.push(ne);
                br[ne.first][ne.second] = br[next.first][next.second] + 1;
            }
        }
    }
}

bool rrast(int x)
{
    queue<pair<int, int> > a;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            tr[i][j] = INF;
            if (fld[i][j] == 'M' and x < br[i][j])
            {
                a.push({i, j});
                tr[i][j] = 0;
            }
        }
    while(!a.empty())
    {
        pair<int, int> next = a.front();
        a.pop();
        for (int i = 0; i < 4; i++)
        {
            pair<int, int> ne = go(next, i);
            if (chesk(ne) and (fld[ne.first][ne.second] == 'G' or fld[ne.first][ne.second] == 'D') and tr[ne.first][ne.second] > tr[next.first][next.second] + 1 and (tr[next.first][next.second] + 1) / s + x < br[ne.first][ne.second])
            {
                a.push(ne);
                tr[ne.first][ne.second] = tr[next.first][next.second] + 1;
            }
        }
    }
    if (tr[fx][fy] != INF)
        return true;
    else
        return false;
}

int main()
{
    cin >> n >> s;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> fld[i][j];
            if (fld[i][j] == 'D')
                fx = i, fy = j;
        }
    rast();
    /*for (int i = 0; i < n; i++)
    {
         for (int j = 0; j < n; j++)
        {
            if (br[i][j] == INF)
                cout << '*' << " ";
            else
                cout << br[i][j] << " ";
        }
        cout << endl;
    }*/
    int l = -1, r = 2 * n * n;
    while (r - l > 1)
    {
        int m = (r + l) / 2;
        if (rrast(m))
            l = m;
        else
            r = m;
    }
    cout << l << endl;
}
