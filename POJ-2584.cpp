/***
* super source當作倉庫,到各個source（S,M,L,X,T）的容量是庫存
* 各個source到第i個人的容量是1或0,取決於這個人能接受的尺寸範圍
* 全部人到super sink的容量是1,因為一人只需要一件衣服
* 若匯流到super sink的流量等於人數,則每個人都有他能接受的衣服
***/
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<map>
using namespace std;

bool DFS(int);
int findflow(int);

#define k 30
#define S 21
#define M 22
#define L 23
#define X 24
#define T 25
#define t 26
map<char,int> m;
int cap[k][k], flow[k][k], path[k], vis[k];

int main(void)
{
	int n, ss, mm, ll, xx, tt;
	string s;
	m['S'] = S;
	m['M'] = M;
	m['L'] = L;
	m['X'] = X;
	m['T'] = T;
	while(cin >> s && s != "ENDOFINPUT") {
		memset(cap,0,sizeof(cap));
		memset(flow,0,sizeof(flow));
		cin >> n;
		for(int i = 1; i <= n; ++i) {
			cin >> s;
			for(int j = m[s[0]]; j <= m[s[1]]; ++j)
				cap[j][i] = 1;
			cap[i][t] = 1;
		}
		scanf("%d %d %d %d %d", &ss, &mm, &ll, &xx, &tt);
		cap[0][S] = ss;
		cap[0][M] = mm;
		cap[0][L] = ll;
		cap[0][X] = xx;
		cap[0][T] = tt;
		int num = 0;
		cin >> s;
		while(1) {
			memset(vis,0,sizeof(vis));
			if(!DFS(0)) break;
			num += findflow(0);
		}
		if(num == n) printf("T-shirts rock!\n");
		else printf("I'd rather not wear a shirt anyway...\n");
	}
	return 0;
}

bool DFS(int s)
{
	vis[s] = 1;
	if(s == t) return true;
	for(int i = 0; i <= t; ++i) {
		if(vis[i]) continue;
		if(cap[s][i] > flow[s][i] || flow[i][s] > 0) {
			path[i] = s;
			if(DFS(i)) return true;
		}
	}
	return false;
}

int findflow(int s)
{
	int f = 1e9;
	for(int i = t, pre; i != s; i = pre) {
		pre = path[i];
		if(cap[pre][i] > flow[pre][i])
			f = min(f,cap[pre][i] - flow[pre][i]);
		else
			f = min(f,flow[i][pre]);
	}
	for(int i = t, pre; i != s; i = pre) {
		pre = path[i];
		if(cap[pre][i] > flow[pre][i])
			flow[pre][i] += f;
		else
			flow[i][pre] -= f;
	}
	return f;
}



































