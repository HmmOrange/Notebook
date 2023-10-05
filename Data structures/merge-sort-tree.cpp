/*
	Author: Orange
	Problem: https://oj.vnoi.info/problem/kquery
*/
#include <bits/stdc++.h>
#define int long long
#define N 30000
#define inf 0x3f3f3f3f
using namespace std;
vector<int> st[4*N + 5];
int a[N + 5];
void build(int id, int l, int r) {
    if (l == r) {
        st[id].push_back(a[l]);
        return;
    }
    
    int mid = (l + r) / 2;
    build(id*2, l, mid);
    build(id*2 + 1, mid + 1, r);

	if (st[id*2].empty()) st[id*2].push_back(0);
	if (st[id*2 + 1].empty()) st[id*2 + 1].push_back(0);
	if (st[id].empty()) st[id].push_back(0);
	
	sort(st[id*2].begin(), st[id*2].end());
	sort(st[id*2 + 1].begin(), st[id*2 + 1].end());
	
	st[id].resize(st[id*2].size() + st[id*2 + 1].size());
	
    merge(st[id*2].begin(), st[id*2].end(),	
          st[id*2 + 1].begin(), st[id*2 + 1].end(), st[id].begin());
 	//cout << "hi" << endl;
}
int get(int id, int l, int r, int u, int v, int k) { // Trả lời truy vấn (x, y, k)
    if (v < l || r < u) {
        return 0;
    }
    if (u <= l && r <= v){
        // Đếm số phần tử > K bằng chặt nhị phân
        return st[id].size() - (upper_bound(st[id].begin(), st[id].end(), k) - st[id].begin());
    }
    int mid = (l + r) / 2;
    return get(id*2, l, mid, u, v, k) + get(id*2+1, mid+1, r, u, v, k);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n;

	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	build(1, 1, n);
	cin >> q;
	while (q--){
		int l, r, k;
		cin >> l >> r >> k;
		cout << get(1, 1, n, l, r) << "\n";
	}
}