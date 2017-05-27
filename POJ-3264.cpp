/***
* segment tree,建好樹後只需查詢,無需更新
***/
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node {
	int maxv, minv;
	Node *l, *r;

	void updata(int v)
	{
		maxv = v;
		minv = v;
	}
	void pull()
	{
		maxv = max(l->maxv,r->maxv);
		minv = min(l->minv,r->minv);
	}
};

Node *build(int,int);
int querymin(Node *,int,int,int,int);
int querymax(Node *,int,int,int,int);
int s[50010];

int main(void)
{
	int n, q, a, b, ma, mi;
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &s[i]);
	Node *root = build(1,n);
	while(q--) {
		scanf("%d %d", &a, &b);
		ma = querymax(root,1,n,a,b);
		mi = querymin(root,1,n,a,b);
		printf("%d\n", ma-mi);
	}
	return 0;
}

Node * build(int L, int R)
{
	Node * now = new Node();
	if(L == R) {
		now->updata(s[L]);
		return now;
	}
	int mid = (L+R)>>1;
	now->l = build(L,mid);
	now->r = build(mid+1,R);
	now->pull();
	return now;
}

int querymin(Node * now,int L, int R, int x, int y)
{
	if(x > R || y < L) return 1e9;
	if(x <= L && y >= R) return now->minv;
	int mid = (L+R)>>1;
	return min( querymin(now->l,L,mid,x,y) , querymin(now->r,mid+1,R,x,y) );
}

int querymax(Node * now,int L, int R, int x, int y)
{
	if(x > R || y < L) return -1e9;
	if(x <= L && y >= R) return now->maxv;
	int mid = (L+R)>>1;
	return max( querymax(now->l,L,mid,x,y) , querymax(now->r,mid+1,R,x,y) );
}
