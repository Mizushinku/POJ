/***
* Binery Indexed Tree應用,將所有路依照東岸城市以及西岸城市,由大到小做二級排序
* 之後依照w（西岸城市編號）作Binery Indexed Tree
* w與自己相同的道路不計算,所以計算w-1
***/
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

long long sum(int);
void modify(int);

struct Node {
	int e, w;
	bool operator<(const Node& cmp) const {
		if(e == cmp.e) return w > cmp.w;
		return e > cmp.e;
	}
}node[1000010];

long long s[1010];
int N, M, K;

int main(void)
{
	int T, cases = 1;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &N, &M, &K);
		for(int i = 0; i < K; ++i) {
			scanf("%d %d", &node[i].e, &node[i].w);
		}
		sort(node,node+K);
		memset(s,0,sizeof(s));
		long long ans = 0;
		for(int i = 0; i < K; ++i) {
			ans += sum(node[i].w-1);
			modify(node[i].w);
		}
		printf("Test case %d: %lld\n", cases++, ans);
	}
	return 0;
}

long long sum(int index)
{
	long long ret = 0;
	while(index > 0) {
		ret += s[index];
		index -= (index&(-index));
	}
	return ret;
}

void modify(int index)
{
	for(int i = index; i <= 1009; i += (i&(-i)))
		++s[i];
}
