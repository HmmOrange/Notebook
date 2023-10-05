#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;
const int inf = 1e18;
int st[5*N + 5];
int st2[5*N + 5];
int a[N + 5];

void update(int id, int l, int r, int i, int v){
	if (i < l || r < i) return;
	if (l == r){
		st[id] = v;
		st2[id] = v;
		return;
	}
	int mid = l + (r - l)/2;
	update(id*2, l, mid, i, v);
	update(id*2 + 1, mid + 1, r, i, v);
	
	st[id] = max(st[id*2], st[id*2 + 1]);
	st2[id] = min(st2[id*2], st2[id*2 + 1]);
}

int get_max(int id, int l, int r, int u, int v){
	if (v < l || r < u) return -inf;
	if (u <= l && r <= v){
		return st[id];
	}
	int mid = l + (r - l)/2;
	return max(get_max(id*2, l, mid, u, v), 
	           get_max(id*2 + 1, mid + 1, r, u, v));
}

int get_min(int id, int l, int r, int u, int v){
	if (v < l || r < u) return inf;
	if (u <= l && r <= v){
		return st2[id];
	}
	int mid = l + (r - l)/2;
	return min(get_min(id*2, l, mid, u, v), 
	           get_min(id*2 + 1, mid + 1, r, u, v));
	           
}


signed main(){
	cin.tie(0)->sync_with_stdio(0);
	memset(st, 0, sizeof(st));
	memset(st2, 0x3f, sizeof(st2));
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++){
		cin >> a[i];
		update(1, 1, n, i, a[i]);
	}
	while (q--){
		int l, r;
		cin >> l >> r;
		cout << get_max(1, 1, n, l, r) - get_min(1, 1, n, l, r) << "\n";
	}
}