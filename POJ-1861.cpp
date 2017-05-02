/***
* 第1行輸入N M,表示有N個點M條路
* 接下來M行輸入u v d,表示u與v號點連通,距離為d,點由1~N號
* 輸出第1行為樹中最大的d,第2行為有N-1條路,接下來N-1行表示各條路
***/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void Union(int,int);
int Find(int);

struct EDGE {
	int u, v, d;
	bool operator<(const EDGE& cmp) const { return d < cmp.d; }
};

vector<int> p(1010), ans;
vector<struct EDGE> edge;

int main(void)
{
	int N, M;
	struct EDGE* e;
	cin >> N >> M;
	for(int i = 1; i <= N; ++i)
		p.at(i) = i;
	for(int i = 0; i < M; ++i) {
		e = new struct EDGE;
		cin >> e->u >> e->v >> e->d;
		edge.push_back(*e);
		delete e;
	}
	sort(edge.begin(),edge.end());
	
	for(int i = 0, count = 0; count < N-1; ++i) {
		int u = edge.at(i).u;
		int v = edge.at(i).v;
		if(Find(u) == Find(v)) continue;

		ans.push_back(i);
		Union(u,v);
		++count;
		if(count == N-1) cout << edge.at(i).d << '\n' << N-1 << endl;
	}
	for(int i = 0; i < ans.size(); ++i)
		cout << edge.at(ans.at(i)).u << ' ' << edge.at(ans.at(i)).v << endl;
	
	return 0;
}

void Union(int u, int v)
{
	int U = Find(u);
	int V = Find(v);
	p.at(U) = V;
}

int Find(int x)
{
	if(x == p.at(x)) return x;
	return p.at(x) = Find(p.at(x));
}
