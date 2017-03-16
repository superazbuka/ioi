#include <iostream>
#include <algorithm>
#include <set>
//1
using namespace std;

const long long INF = 1e18;

pair<long long, long long> k[500000];
pair<pair<long long, long long>, long long> nmas[500000];
long long n, w;

struct cmp
{
    bool operator()(pair<pair<long long, long long>, long long> a, pair<pair<long long, long long>, long long> b)
    {
        return a.first.first * b.first.second < b.first.first * a.first.second or ( a.first.first * b.first.second == b.first.first * a.first.second and a.first < b.first);
    }
};

bool les(pair<pair<long long, long long>, long long> a, pair<pair<long long, long long>, long long> b)
{
    return a.first.first * b.first.second < b.first.first * a.first.second or ( a.first.first * b.first.second == b.first.first * a.first.second and a.first < b.first);
}

int main()
{
    cin >> n >> w;
    for (long long i = 0; i < n; i++)
    {
        cin >> k[i].first >> k[i].second;
        nmas[i] = {k[i], i};
    }
    sort(nmas, nmas + n, les);
    double sum = 0;
    set<pair<long long, int> > a;
    int goog = 0;
    int ind = 0;
    for (int i =  0; i < n; i++)
    {
        sum += nmas[i].first.second;
        a.insert( {nmas[i].first.second, nmas[i].second});
        while(sum * nmas[i].first.first > w * nmas[i].first.second)
        {
            auto x = a.end();
            x--;
            sum -= (*x).first;
            a.erase(x);
        }
        if (goog < a.size())
        {
            goog = a.size();
            ind = i;
        }
    }
    cout << goog << endl;
    while(!a.empty())
    {
        a.erase(a.begin());
    }
    sum = 0;
    for (int i =  0; i < ind + 1; i++)
    {
        sum += nmas[i].first.second;
        a.insert( {nmas[i].first.second, nmas[i].second});
        while(sum * nmas[i].first.first > w * nmas[i].first.second)
        {
            auto x = a.end();
            x--;
            sum -= (*x).first;
            a.erase(x);
        }
    }
    for (auto i: a)
    {
        cout << i.second + 1 << endl;
    }
}
