/*
	Author: Orange
	Problem: https://oj.vnoi.info/problem/qmax2
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
const int inf = 1e18;
struct Node{
	int lazy;
	int val;
} st[4*N + 5];
int a[N + 5];

void down(int id){
	int t = st[id].lazy;
	
	st[id*2].lazy += t;
	st[id*2].val += t;
	
	st[id*2 + 1].lazy += t;
	st[id*2 + 1].val += t;
	
	st[id].lazy = 0;
}

void update(int id, int l, int r, int u, int v, int k){
	if (v < l || r < u) return;
	if (u <= l && r <= v){
		st[id].lazy += k;
		st[id].val += k;
		return;
	}
	down(id);
	int mid = l + (r - l)/2;
	
	update(id*2, l, mid, u, v, k);
	update(id*2 + 1, mid + 1, r, u, v, k);
	
	st[id].val = max(st[id*2].val, st[id*2 + 1].val);
}

int get(int id, int l, int r, int u, int v){
	if (v < l || r < u) return -inf;
	if (u <= l && r <= v) return st[id].val;
	
	down(id);
	int mid = l + (r - l)/2;
	
	return max(get(id*2, l, mid, u, v), 
		   	   get(id*2 + 1, mid + 1, r, u, v));
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	
	for (int i = 1, u, v, k; i <= q; i++){
		int t;
		cin >> t;
		if (t == 0){
			cin >> u >> v >> k;
			update(1, 1, n, u, v, k);
		}
		else{
			cin >> u >> v;
			cout << get(1, 1, n, u, v) << "\n";
		}
	}
}