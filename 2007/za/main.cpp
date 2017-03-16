#include <iostream>
#include <string>

using namespace std;

long long n;

struct point
{
    long long x, y;
};

bool chesk(long long x, long long y)
{
    if (x > n or x <= 0 or y > n or y <= 0)
        return false;
    cout << "examine " << x << " " << y << endl;
    string s;
    cin >> s;
    if (s == "true")
        return true;
    else
        return false;
}

int main()
{
    point s;
    cin >> n >> s.x >> s.y;
    long long len = 1;
    while(chesk(s.x + len, s.y))
    {        
        len = len * 2;
    }
    long long l = s.x, r = s.x + len + 1;
    point x;
    while(r - l > 1)
    {
        long long m = (l + r) / 2;
        if (chesk(m, s.y))
            l = m;
        else
            r = m;
    }
    long long m = l;
    len = 1;
    while(chesk(s.x - len, s.y))
    {
        len = len * 2;
    }
    l = s.x - len - 1, r = s.x;
    while(r - l > 1)
    {
        long long m = (l + r) / 2;
        if (chesk(m, s.y))
            r = m;
        else
            l = m;
    }
    m = m - r + 1;
    x.x = r + m / 2;
    len = 1;
    while (chesk(s.x, s.y + len))
    {
        len *= 2;
    }
    l = s.y, r = s.y + len;
    while(r - l > 1)
    {
        long long m = (r + l) / 2;
        if (chesk(s.x, m))
            l = m;
        else
            r = m;
    }
    x.y = l - m / 2;
    while (chesk(x.x, x.y))
    {
        x.x -= m;
        x.y -= m;
    }
    x.x += m;
    x.y += m;
    while (chesk(x.x, x.y))
    {
        x.x -= 2 * m;
    }
    x.x += 2 * m;
    while (chesk(x.x, x.y))
    {
        x.y -= 2 * m;
    }
    x.y += 2 * m;
    x.x += 2 * m;
    x.y += 2 * m;
    cout << "solution " << x.x << " " << x.y << endl;
}
  
