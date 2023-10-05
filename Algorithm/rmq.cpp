#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int N = 5e5 + 5;
const int K = 30;
const int inf = 1e18;
vector<pii> a[N];
int b[N], ind[N], cnt = 0;
int h[N], parent[N], tin[N], tout[N], tfin[N];
int ttime = 0;
int n, m;
void tree(int pre, int u){
	parent[u] = pre;
	tin[u] = ++ttime;
	tfin[ttime] = u;
	b[++cnt] = u;
	ind[u] = cnt;
	for (auto i: a[u]){
		int v = i.first;
		int t = i.second;
		if (v == pre) continue;
		h[v] = h[u] + t;
		tree(u, v);
		b[++cnt] = u;
	}
	tout[u] = ttime;
}

//Sparse Table & RMQ
int st[N][K], plog[N];
void prelog(){
	plog[1] = 0;
	for (int i = 2; i < N; i++){
		plog[i] = plog[i/2] + 1;
	}
}

void sparse(){
	for (int i = 0; i < cnt; i++){
		st[i][0] = tin[b[i + 1]];
	}
	for (int j = 1; j < K; j++){
		for (int i = 0; i + (1LL << j) < cnt; i++){
			st[i][j] = min(st[i][j - 1], st[i + (1LL << (j - 1))][j - 1]);
			//i -> i + 2^j - 1
			//= i -> i + 2^(j - 1) - 1 | i + 2^(j - 1) -> i + 2^j - 1
		}
	}
}
int rmq(int l, int r){
	int j = plog[r - l + 1];
	return min(st[l][j], st[r - (1 << j) + 1][j]);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1, u, v, t; i < n; i++){
		cin >> u >> v >> t;
		a[u].push_back({v, t});
		a[v].push_back({u, t});
	}
	tout[0] = inf;
	tree(0, 1);
	prelog();
	sparse();
	for (int i = 1, s, t; i <= m; i++){
		cin >> s >> t;
		int l = ind[s] - 1;
		int r = ind[t] - 1;
		if (l > r) swap(l, r);
		int f = tfin[rmq(l, r)];
		cout << h[s] + h[t] - 2*h[f] << "\n";
	}
}