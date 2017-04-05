#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
bool Relax(int,int,int);

struct node {
	vector<int> v[2];
}land[1001];

int dis[1001] = {0};

int main(void)
{
	int T, N;
	int inf = 2*1e9;
	for(int i = 0; i < 1001; ++i) dis[i] = inf;
	cin >> T >> N;
	dis[N] = 0;
	while(T--) {
		int a, b, d;
		cin >> a >> b >> d;
		land[a].v[0].push_back(b); land[a].v[1].push_back(d);
		land[b].v[0].push_back(a); land[b].v[1].push_back(d);
	}
	queue<int> que;
	bool inque[1001] = {false};
	que.push(N);
	inque[N] = true;
	while(!que.empty()) {
		int now = que.front();
		inque[now] = false;
		que.pop();
		for(int i = 0; i < land[now].v[0].size(); ++i) {
			int v = land[now].v[0][i];
			int d = land[now].v[1][i];
			if( Relax(now,v,d) ) {
				if(!inque[v]) {
					que.push(v);
					inque[v] = true;
				}
			}
		}
	}
	cout << dis[1] << endl;
	return 0;
}

bool Relax(int u, int v, int d)
{
	if(dis[u] + d < dis[v]) {
		dis[v] = dis[u] + d;
		return true;
	}
	return false;
}
