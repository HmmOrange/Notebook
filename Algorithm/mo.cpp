/*
	Author: Orange
	Problem: https://codeforces.com/contest/86/problem/D
*/	
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
struct query{
	int l, r, i;
} q[N];
int a[N], ans[N], cnt[N];
int s = 0;
void add(int x){
	s -= cnt[a[x]]*cnt[a[x]]*a[x];
	cnt[a[x]]++;
	s += cnt[a[x]]*cnt[a[x]]*a[x];
}
void remove(int x){
	s -= cnt[a[x]]*cnt[a[x]]*a[x];
	cnt[a[x]]--;
	s += cnt[a[x]]*cnt[a[x]]*a[x];
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, t;
	cin >> n >> t;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= t; i++){
		cin >> q[i].l >> q[i].r;
		q[i].i = i;
	}
	
	// Hilbert curve
	int ss = max(1ll, (int)(n/sqrt(t)));
	auto cmp = [&](query a, query b){
		if (a.l/ss != b.l/ss) return a.l < b.l; 
    	else if((a.l/ss) % 2 == 0) return a.r > b.r;
    	else return a.r < b.r;
	};
	sort(q + 1, q + t + 1, cmp);
	
	for (int j = q[1].l; j <= q[1].r; j++){
		add(j);
	}
	ans[q[1].i] = s;
	for (int i = 2; i <= t; i++){
		int ll = q[i].l, rr = q[i].r;
		while (ll < q[i - 1].l) add(ll++);
		while (rr > q[i - 1].r) add(rr--);
		while (ll > q[i - 1].l) remove(--ll);
		while (rr < q[i - 1].r) remove(++rr);
		ans[q[i].i] = s;
	}
	for (int i = 1; i <= t; i++){
		cout << ans[i] << "\n";
	}
	
}