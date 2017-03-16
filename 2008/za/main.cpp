#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 25000 * 20 + 5;

int go[MAXN][26];
bool flag[MAXN];
int deep[MAXN];
int ln = 1;

void add(const string &s)
{
    int tec = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (go[tec][s[i] - 'a'] != -1)
            tec = go[tec][s[i] - 'a'];
        else
        {
            go[tec][s[i] - 'a'] = ln;
            tec = ln;
            ln++;
        }
    }
    flag[tec] = true;
}

vector<char> ans;

int cnt = 0;
int n;

void dfs(int v)
{
    if (flag[v])
    {
        ans.push_back('P');
        cnt++;
        if (cnt == n)
        {
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++)
            {
                cout << ans[i] << '\n';
            }
            exit(0);
        }
    }
    int dst = 0;
    for (int i = 0; i < 26; i++)
    {
        if (go[v][dst] == - 1 or (go[v][i] != -1 and deep[go[v][i]] > deep[go[v][dst]]))
            dst = i;
    }
    for (int i = 0; i < 26; i++)
    {
        if (go[v][i] != -1 and i != dst)
        {
            ans.push_back(char('a' + i));
            dfs(go[v][i]);
            ans.push_back('-');
        }
    }
    if (go[v][dst] != -1)
    {
        ans.push_back(char('a' + dst));
        dfs(go[v][dst]);
        ans.push_back('-');
    }
}

void dfsd(int v)
{
    int ans = 0;
    for (int i = 0; i < 26; i++)
    {
        if (go[v][i] != -1)
        {
            dfsd(go[v][i]);
            ans = max(ans, deep[go[v][i]]);
        }
    }
    deep[v] = ans + 1;
}

int main()
{
    //freopen("printer.in", "r", stdin);
    //freopen("C:\IOI\", "w", stdout);
    ios::sync_with_stdio(false);
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < 26; j++)
            go[i][j] = -1;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        add(s);
    }
    dfsd(0);
    dfs(0);
}
