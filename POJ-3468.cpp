/***
* Binary Indexed Tree -> zwk線段樹
* delta[i] = delta[i] + v 代表原始陣列中s[i]...s[n]都共同增加v
* 因此要將s[s]~s[t]都加v,需將delta[s] = delta[s] + v 且 delta[t+1] = delta[t+1] + (-v)
***/
#include<cstdio>
#include<iostream>
using namespace std;

long long getsum(const long long *,int);
void modify(long long *,int,int);

long long s[100010] = {0};
long long s1[100010] = {0};
long long s2[100010] = {0};
int N, Q;


int main(void)
{
	int k, a, b, c;
	char od;
	scanf("%d %d", &N, &Q);
	for(int i = 1; i <= N; ++i) {
		scanf("%lld", &s[i]);
		s[i] += s[i-1];
	}
	for(int i = 0; i < Q; ++i) {
		scanf("%c", &od);
		scanf("%c", &od);
		if(od == 'Q') {
			scanf("%d %d", &a, &b);
			long long t1 = 0, t2 = 0, t3 = 0;
			//sum[x] = segma(org[i]) + (x+1)*segma(delta[i]) - segma(delta[i]*i) 1 <= i <= x
			t1 = s[b] - s[a-1];  // b的segma(org[i]) - (a-1)的segma(org[i])
			t2 = (b+1)*getsum(s1,b) - getsum(s2,b); //b的後兩項
			t3 = (a-1+1)*getsum(s1,a-1) - getsum(s2,a-1); //(a-1)的後兩項
			printf("%lld\n", t1+t2-t3);
		}
		else {
			scanf("%d %d %d", &a, &b, &c);
			modify(s1,a,c); 
			modify(s1,b+1,-c);
			modify(s2,a,a*c);
			modify(s2,b+1,-(b+1)*c);
		}
	}
	
	return 0;
}

long long getsum(const long long *k, int index)
{
	long long ans = 0;
	while(index > 0) {
		ans += k[index];
		index -= (index&(-index));
	}
	return ans;
}

void modify(long long *k, int index, int v)
{
	for(int i = index; i <= N; i += (i&(-i))) {
		k[i] += v;
	}
}
