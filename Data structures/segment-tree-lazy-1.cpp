//https://oj.vnoi.info/problem/qmax
#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define N (int)5e5 + 5
using namespace std;
int st[4*N];
int add[4*N];
void update(int id, int l, int r, int u, int v, int k){
	if (l > r || v < l || r < u) return;
	if (u <= l && r <= v){
		st[id] += k;
		add[id] += k;
		return;
	}
	int mid = l + (r - l)/2;
	
	update(id*2, l, mid, u, v, k);
	update(id*2 + 1, mid + 1, r, u, v, k);
	
	st[id] = max(st[id*2], st[id*2 + 1]) + add[id];
}

int get(int id, int l, int r, int u, int v){
	if (l > r || v < l || r < u) return -inf;
	if (u <= l && r <= v) return st[id];
	
	int mid = l + (r - l)/2;
	return max(get(id*2, l, mid, u, v), 
		   	   get(id*2 + 1, mid + 1, r, u, v)) + add[id];
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1, u, v, k; i <= m; i++){
		cin >> u >> v >> k;
		update(1, 1, n, u, v, k);
	}
	int q;
	cin >> q;
	while (q--){
		int l, r;
		cin >> l >> r;
		cout << get(1, 1, n, l, r) << "\n";
	}
}