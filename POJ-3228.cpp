/***
* 原本是二分搜尋+最大流（金礦量為super source,金礦儲存量為super sink）
* 因為每條路的cap都為inf,所以利用disjoint set,將相連的點的gold與store合併
* 有點類似單位A納入單位B麾下的感覺,代表（A+B）的B稱為boss
* 為了找出儘可能短的d,由最短的數組開始合併,直至所有boss都滿足store >= gold
***/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int Find(int);
void Union(const int&,const int&);

#define k 210

struct EDGE {
	int u, v, d;
	bool operator<(const EDGE& cmp) const { return d < cmp.d; }
}edge[20010];

int p[k], gold[k], store[k];

int main(void)
{
	int N, M, ans;
	while(cin >> N && N) {
		bool flag = false;
		for(int i = 1; i <= N; ++i) {
			cin >> gold[i];
			p[i] = i;
		}
		for(int i = 1; i <= N; ++i) {
			cin >> store[i];
			if(store[i] < gold[i]) {
				flag = true;
			}
		}
		if(!flag) { cout << 0 << endl; continue; }

		cin >> M;
		for(int i = 0; i < M; ++i) {
			cin >> edge[i].u >> edge[i].v >> edge[i].d;
		}
		sort(edge,edge+M);
		
		for(int i = 0; i < M; ++i) {
			int fu = Find(edge[i].u), fv = Find(edge[i].v);
			if(fu == fv) continue;
			
			flag = false;
			Union(fu,fv);
			ans = edge[i].d;
			for(int j = 1; j <= N; ++j) {
				int boss = Find(j);
				if(store[boss] < gold[boss]) flag = true;
			}
			if(!flag) break;
		}
		flag ? cout << "No Solution" << endl : cout << ans << endl;
	}
	return 0;
}

int Find(int x)
{
	if(x == p[x]) return x;
	return p[x] = Find(p[x]);
}

void Union(const int &fu,const int &fv)
{
	p[fu] = fv;
	gold[fv] += gold[fu];
	store[fv] += store[fu];
}
