#include<iostream>
#include<vector>
using namespace std;
#define inf 1e9

typedef struct EDGE {
	int beg, end, time;
	EDGE(int s, int e, int t)
	{
		beg = s; end = e; time = t;
	}
}EDGE;

int main(void)
{
	int F, N, M, W, S, E, T, i, j;
	EDGE *p, *q;
	vector<EDGE> edge;
	vector<int> dis(501);
	cin >> F;
	while(F--) {
		cin >> N >> M >> W;
		dis.at(1) = 0;
		for(i = 2; i <= N; ++i) {
			if(dis.at(i) != inf) dis.at(i) = inf;
		}

		for(i = 0, j = 0; i < M; ++i) {
			cin >> S >> E >> T;
			p = new EDGE(S,E,T);
			q = new EDGE(E,S,T);
			edge.push_back(*p);
			edge.push_back(*q);
			delete p; delete q;
		}
		for(i = 0; i < W; ++i) {
			cin >> S >> E >> T;
			p = new EDGE(S,E,-T);
			edge.push_back(*p);
			delete p;
		}
		for(i = 1; i < N; ++i) {
			for(j = 0; j < edge.size(); ++j) {
				S = edge.at(j).beg;
				E = edge.at(j).end;
				T = edge.at(j).time;
				if(dis.at(S) + T < dis.at(E)) {
					dis.at(E) = dis.at(S) + T;
				}
			}
		}
		bool neg_cyc = false;
		for(j = 0; j < edge.size(); ++j) {
			S = edge.at(j).beg;
			E = edge.at(j).end;
			T = edge.at(j).time;
			if(dis.at(S) + T < dis.at(E)) {
				neg_cyc = true;
			}
		}
		neg_cyc ? cout << "YES" << endl : cout << "NO" << endl;
		edge.clear();
	}
	return 0;
}
