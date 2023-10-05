/*
	Author: Orange
	Problem: https://oj.vnoi.info/problem/icpc22_mt_d
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;
vector<int> st[4*N + 5];
pair<int, int> a[N + 5];
int b[N];
void merge_v(int id){
	int i = 0, j = 0;	
	while (i < (int)st[id*2].size() || j < (int)st[id*2 + 1].size()){
		if (i < (int)st[id*2].size() && j < st[id*2].size() && st[id*2][i] < st[id*2 + 1][j]){
			st[id].push_back(st[id*2][i++]);
		}
		else if (j < (int)st[id*2 + 1].size()) 
			st[id].push_back(st[id*2 + 1][j++]);
		else 
			st[id].push_back(st[id*2][i++]);
	}
}
void build(int id, int l, int r) {
    if (l == r) {
        st[id].push_back(a[l].second);
        return;
    }

    int mid = (l + r) / 2;
    build(id*2, l, mid);
    build(id*2 + 1, mid + 1, r);
	merge_v(id);
}

int count_range(int id, int l, int r){
	auto L = lower_bound(st[id].begin(), st[id].end(), l);
	auto R = upper_bound(st[id].begin(), st[id].end(), r);
	return R - L;
}
int walk(int id, int l, int r, int u, int v, int k){
	if (l == r) return st[id][0];
	
	int mid = l + (r - l)/2;
	int cnt = count_range(id * 2, u, v);
	if (k <= cnt) 
		return walk(id*2, l, mid, u, v, k);
	return walk(id*2 + 1, mid + 1, r, u, v, k - cnt);
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++){
		cin >> b[i];
		a[i].first = b[i];
		a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	build(1, 1, n);
	while (q--){
		int l, r;
		cin >> l >> r;
		cout << b[walk(1, 1, n, l, r, (r - l + 2)/2)] << "\n";
	}
}
