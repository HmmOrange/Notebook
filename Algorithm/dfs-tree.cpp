/*
	Date: 16/7/2022
	Problem: CAPITAL
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
vector<int> a[N];
int parent[N], tin[N], tout[N], low[N], root[N];
int ttime = 0;
int joint[N], bridge[N], c[N], jointCnt = 0, bridgeCnt = 0;
int n, m, comp = 0;
void dfs(int pre, int u){
	int child = 0;
	low[u] = tin[u] = ++ttime;
	for (auto v: a[u]){
		if (v == pre) continue;
		if (!tin[v]){
			parent[v] = u;
			dfs(u, v);
			low[u] = min(low[u], low[v]);
			child++;
			
			// Checking joint
			if (pre == 0){ // If root
				if (child > 1){
					joint[u]++;
				}
			}
			else if (low[v] >= tin[u]) joint[u]++;
			
			// Checking bridge
			if (low[v] == tin[v]){
				bridge[v]++;
			}
		}
		else{
			low[u] = min(low[u], tin[v]);
		}
	}
	tout[u] = ttime;
}

bool ancestor(int u, int v){
	return tin[u] <= tin[v] && tout[v] <= tout[u];
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	tin[0] = 1e9;
	for (int i = 1; i <= n; i++){
		if (tin[i] == 0) comp++, root[i]++, dfs(0, i);
	}
	/*
	for (int i = 1; i <= n; i++){
		if (joint[i]){
			vector<int> f;
			for (auto v: a[i]){
				if (tin[v] > tin[i]) f.push_back(v);
				//cout << i << " " << v << "\n";
			}
			sort(f.begin(), f.end(), [](int a, int b){
				return tin[a] < tin[b];
			});
			int cur = 0;
			int cnt = 0;
			for (auto v: f){
				if (low[v] < tin[i]) continue;
				if (cur != 0){
					if (!ancestor(cur, v)){
						c[i]++;
						cur = v;
					}
				}
				else{
					cur = v;
					c[i]++;
				}
				//cout << cur << " " << v << "\n";
			}
			if (root[i]) c[i]--;
			//cout << i << "->" << c[i] << "\n";
		}
	}
	*/
	int res = n;
	for (int i = n - 1; i >= 1; i--){
		if (joint[i] >= joint[res]){
			res = i;
		}
	}
	cout << (joint[res] + 1) + (comp - 1) << " " << res << "\n";
}
