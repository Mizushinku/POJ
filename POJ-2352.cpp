#include<cstdio>
#include<vector>
using namespace std;
#define k 32010


int main(void)
{
	int N, x, y;
	vector<int> level(15010), s(k);
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		scanf("%d %d", &x, &y);
		++x;
		for(int j = x; j < k; j += (j&(-j))) {
			++s[j];
		}
		int sum = 0;
		while(x > 0) {
			sum += s[x];
			x -= (x&(-x));
		}
		++level[sum-1];
	}
	for(int i = 0; i < N; ++i)
		printf("%d\n", level[i]);
	return 0;
}
