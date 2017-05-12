/***
* 將gopher與hole視為二分圖兩邊,檢查一隻gopher與每一個洞間的距離
* 若距離滿足條件（可再時限內到達）,則記錄該條編
* 最後作最大匹配數,得出生存的gopher數目
***/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool DFS(int);

#define k 110

class pos {
public :
	double x, y;
};

pos gopher[k], hole[k];
int llink[k], rlink[k], vis[k];
vector<int> edge[k];

int main(void)
{
	int n, m, s, v;
	while(cin >> n >> m >> s >> v) {
		for(int i = 1; i <= n; ++i) {
			cin >> gopher[i].x >> gopher[i].y;
		}
		for(int i = 1; i <= m; ++i) {
			cin >> hole[i].x >> hole[i].y;
		}

		for(int i = 1; i <= n; ++i) {
			double x1 = gopher[i].x;
			double y1 = gopher[i].y;
			for(int j = 1; j <= m; ++j) {
				double x2 = hole[j].x;
				double y2 = hole[j].y;
				if(((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) <= s*v*s*v) {
					edge[i].push_back(j);
				}
			}
		}
		
		int ans = 0;
		memset(llink,0,sizeof(llink));
		memset(rlink,0,sizeof(rlink));
		for(int i = 1; i <= n; ++i) {
			memset(vis,0,sizeof(vis));
			if(DFS(i)) ++ans;
		}
		cout << n - ans << endl;
		for(int i = 0; i <= k; ++i)
			edge[i].clear();
	}
	return 0;
}

bool DFS(int cur)
{
	int next;

	for(int i = 0; i < edge[cur].size(); ++i) {
		next = edge[cur][i];
		if(!vis[next]) {
			vis[next] = 1;
			if(!rlink[next] || DFS(rlink[next])) {
				llink[cur] = next;
				rlink[next] = cur;
				return true;
			}
		}
	}
	return false;
}
