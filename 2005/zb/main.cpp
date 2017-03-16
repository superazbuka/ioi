#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int a[5000000];
int cl = -1e9, cr = 1e9;

int main()
{
	#ifdef ONPC
		freopen("a.in", "r", stdin);
		freopen("a.out", "w", stdout);
	#endif
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		cr = min(cr, a[i]);
		cl = 2 * a[i] - cl;
		cr = 2 * a[i] - cr;
		if (cl >= cr)
			swap(cl, cr);
		else
		{
			cout << 0 << endl;
			return 0;
		}
	}
	cout << cr - cl + 1 << endl;
	return 0;
}


