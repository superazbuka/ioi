#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

typedef unsigned int index;

int f(size_t x)
{
	while ((x & 1) != 0)
		x = x >> 1;
	return (int)x >> 1;
}

int main()
{
#ifdef ONPC
#else
#endif
	while (true)
	{
		int xr, yr;
		cin >> xr >> yr;
		if (xr == -1)
			return 0;
		size_t x = (size_t)xr, y = (size_t)yr;
		if (f(x) > f(y))
		{
			size_t ans = 0;
			while (f(x) != f(y))
				x--, ans++;
			cout << "V " << ans << endl;
		}
		else
		{
			size_t ans = 0;
			while (f(x) != f(y))
				y--, ans++;
			cout << "H " << ans << endl;
		}
	}
}
