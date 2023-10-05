#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 5e5 + 5;
const int inf = 1e18;

int n, m, tin[N], tout[N], low[N];
vector<int> a[N];
stack<int> st;
int ttime = 0;
int scc = 0;
map<int, int> mp[N];
vector<int> ans[N];
int cnt[N];
int id[N];
void dfs(int pre, int u) {
    low[u] = tin[u] = ++ttime;
    st.push(u);
    for (auto v: a[u]){
        if (!tin[v]){
            dfs(u, v);
            low[u] = min(low[u], low[v]);
        }
        else{
            low[u] = min(low[u], tin[v]);
        }
	}
    if (tin[u] == low[u]){ 
	    scc++;
        int v;
        do{
            v = st.top();
            id[v] = scc;
            ans[scc].push_back(v);
            st.pop();
            tin[v] = low[v] = inf;
        } 
        while (v != u);
    }
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    int u, v;
   	while (cin >> u >> v){
        a[u].push_back(v);
    }
	for (int i = 1; i <= n; i++){
		if (a[i].size() == 0) return cout << 1 << "\n" << i, 0;
	}
    for (int i = 1; i <= n; i++){
        if (!tin[i]) dfs(0, i);
	}	
	for (int i = 1; i <= n; i++){
		for (auto v: a[i]){
			if (id[v] != id[i]){
				cnt[id[i]]++;
			}
		}
	}
	int minf = 0;
	for (int i = 1; i <= scc; i++){
		if (cnt[i]) continue;
		if (minf == 0 || ans[i].size() < ans[minf].size()) minf = i;
	}
	cout << ans[minf].size() << "\n";
	for (auto i: ans[minf]) cout << i << " ";
}
