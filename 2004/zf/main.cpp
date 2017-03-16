#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cassert>


typedef unsigned int index;

namespace cnst
{
}

int main()
{
#ifdef ONPC
	assert(freopen("a.in", "r", stdin));
	assert(freopen("a.out", "w", stdout));
#else
#endif
	size_t w, h;
	std::cin >> w >> h;
	std::vector<std::vector<int> > d(w, std::vector<int>(h));
	for (index i = 0; i < w; i++)
		for (index j = 0; j < h; j++)
			d[i][j] = (int)((i + 1) * (j + 1));
	size_t n;
	std::cin >> n;
	for (index i = 0; i < n; i++)
	{
		index curw, curh;
		std::cin >> curw >> curh;
		d[curw - 1][curh - 1] = 0;
	}
	for (index i = 1; i < w; i++)
		for (index j = 1; j < h; j++)
		{
			for (index k = 0; k < i; k++)
			{
				d[i][j] = std::min(d[i][j], d[k][j] + d[i - k - 1][j]);
			}
			for (index k = 0; k < j; k++)
			{
				d[i][j] = std::min(d[i][j], d[i][k] + d[i][j - k - 1]);
			}
		}
	std::cout << d[w - 1][h - 1] << std::endl;
}

