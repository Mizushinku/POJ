/***
* 因為要求的是比第i之牛更"強壯"的牛隻數,所以將牛先以E由大到小排,E一樣再由S由小到大排
* 如此一來,排序後第i之牛前面的牛隻數即是答案
* 利用Binary Indexed Tree實作
***/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;

#define k 100010

struct NODE {
	int index, S, E;
	bool operator<(const NODE& cmp) const {
		if(E == cmp.E) return S < cmp.S;
		return E > cmp.E;
	}
}node[k];

int s[k],ans[k];

int main(void)
{
	int N,S,E;
	while(cin >> N && N) {
		int MS = 0;
		for(int i = 0; i < N; ++i) {
			scanf("%d %d", &S,&E);
			node[i].S = ++S;
			node[i].E = ++E;
			node[i].index = i;
			MS = max(MS,node[i].S);
		}
		sort(node,node+N);
		
		memset(s,0,sizeof(s));
		for(int i = 0; i < N; ++i) {
			if(i && node[i-1].E == node[i].E && node[i-1].S == node[i].S) {
				ans[node[i].index] = ans[node[i-1].index]; // E與S都和前一隻一樣的話,ans相等
				for(int j = node[i].S; j <= MS; j += (j&(-j))) {
					++s[j];
				}
			}
			else {
				for(int j = node[i].S; j <= MS; j += (j&(-j))) {
					++s[j];
				}
				int sum  = 0;
				int tmp = node[i].S;
				while(tmp > 0) {
					sum += s[tmp];
					tmp -= (tmp & (-tmp));
				}
				ans[node[i].index] = sum-1; //本身不算所以-1
			}
		}
		for(int i = 0; i < N; ++i) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}
