/***
* 第1行輸入N M,代表有N個點（編號1~N）,M條路
* 接下來M行輸入u v d,代表u、v點間互通的路距離d
* 輸出為最小生成樹的最大路徑
***/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace  std;

int Find(int);
void Union(int,int);

struct EDGE {
	int u, v, d;
	bool operator<(const EDGE& cmp) const { return d < cmp.d; }
};
vector<int> p(2010);

int main (void)
{
	int N, M;
	cin >> N >> M;
	vector<struct EDGE> edge(10010);
	for(int i = 1; i <= N; ++i)
		p.at(i) = i;
	for(int i = 0; i < M; ++i)
		cin >> edge.at(i).u >> edge.at(i).v >> edge.at(i).d;
	sort(edge.begin(),edge.end());

	for(int i = 0, count = 0; count < N-1; ++i) {
		int a = edge.at(i).u, b = edge.at(i).v;
		if(Find(a) == Find(b)) continue;

		Union(a,b);
		++count;
		if(count == N-1) cout << edge.at(i).d << endl;
	}

	return 0;
}

int Find(int x)
{
	if(x == p.at(x)) return x;
	return p.at(x) = Find(p.at(x));
}

void Union(int a, int b)
{
	int A = Find(a);
	int B = Find(b);
	p.at(A) = B;
}
