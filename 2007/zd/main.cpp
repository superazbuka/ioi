#include <iostream>
#include <string>

using namespace std;

int a1[4][4][4][4];
int a2[4][4][4][4];
string st;

int cnt(int a, int b, int c)
{
    int tmp[] = {0, 0, 0, 0};
    tmp[a] = 1;
    tmp[b] = 1;
    tmp[c] = 1;
    return tmp[0] + tmp[1] + tmp[2]; 
}

int ret(char g)
{
    if (g == 'M')
        return 1;
    if (g == 'B')
        return 0;
    if (g == 'F')
        return 2;
}
    

int main()
{
    int n;
    cin >> n;
    cin >> st;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int s= 0; s < 4; s++)
                {
                    a1[i][k][j][s] = -10000;
                    a2[i][k][j][s] = -10000;
                }
    a1[3][3][3][3] = 0;
    for (int pos = 1; pos <= n; pos++)
    {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int s = 0; s < 4; s++)
                {
                    a2[j][ret(st[pos - 1])][k][s] = max(a2[j][ret(st[pos - 1])][k][s], a1[i][j][k][s] + cnt(i, j, ret(st[pos - 1])));                      
                    a2[i][j][s][ret(st[pos - 1])] = max(a2[i][j][s][ret(st[pos - 1])], a1[i][j][k][s] + cnt(k, s, ret(st[pos - 1]))); 
                }   
        swap(a1, a2);
        for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int s= 0; s < 4; s++)
                    a2[i][j][k][s] = -10000;
    }
    int mmax = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                for (int s= 0; s < 4; s++)
                {
                    mmax = max(mmax, a1[i][j][k][s]);
                }
    cout << mmax;
    return 0;
}
