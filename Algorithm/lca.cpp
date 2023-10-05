#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int N = 1e5 + 5;
const int K = 20;
const int inf = 1e18;
vector<pii> a[N];
int h[N], parent[N], tin[N], tout[N];
int ttime = 0;
int n, m;
void tree(int pre, int u){
	parent[u] = pre;
	tin[u] = ++ttime;
	for (auto i: a[u]){
		int v = i.first;
		int t = i.second;
		if (v == pre) continue;
		h[v] = h[u] + t;
		tree(u, v);
	}
	tout[u] = ttime;
}

//LCA
int p[K][N];
void binlift(){
	for (int i = 1; i <= n; i++){
		p[0][i] = parent[i];
	}
	for (int j = 1; j < K; j++){
		for (int i = 1; i <= n; i++){
			p[j][i] = p[j - 1][p[j - 1][i]];
		}
	}
}
bool ancestor(int u, int v){
	return tin[u] <= tin[v] && tout[v] <= tout[u];
}
int lca(int u, int v){
	if (ancestor(u, v)) return u;
	if (ancestor(v, u)) return v;
	for (int j = K - 1; j >= 0; j--){
		if (!ancestor(p[j][u], v)) u = p[j][u];
	}
	return p[0][u];
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
	binlift();
	for (int i = 1, s, t; i <= m; i++){
		cin >> s >> t;
		int f = lca(s, t);
		cout << h[s] + h[t] - 2*h[f] << "\n";
	}
}