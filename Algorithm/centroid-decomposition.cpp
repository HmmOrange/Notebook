#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
const int K = 17;
const int inf = 1e18;

int n, m;
vector<int> a[N];
int tin[N], tout[N], h[N], pa[N], ttime = 0;
int p[K][N];
void dfs(int pre, int u){
    tin[u] = ++ttime;
    h[u] = h[pre] + 1;
    p[0][u] = pre;
    for (auto v: a[u]){
        if (pre == v) continue;
        dfs(u, v);
    }
    tout[u] = ttime;
}
void binlift(){
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
    for (int i = K - 1; i >= 0; i--){
        if (!ancestor(p[i][u], v)) u = p[i][u];
    }
    return p[0][u];
}
int dist(int u, int v){
    return h[u] + h[v] - 2 * h[lca(u, v)];
}
struct CD{
    int n;
    vector<int> pa, sz, ans;
    CD(int n): n(n), pa(n + 1), sz(n + 1), ans(n + 1){
        for (int i = 1; i <= n; i++) ans[i] = inf;
    }
    void dfs(int pre, int u){
        sz[u] = 1;
        for (auto v: a[u]){
            if (pre == v || pa[v]) continue;
            dfs(u, v);
            sz[u] += sz[v];
        }
    }
    int centroid(int pre, int u, int n){
        for (auto v: a[u]){
            if (pre == v || pa[v]) continue;
            if (sz[v] > n/2) return centroid(u, v, n);
        }
        return u;
    }
    void build(int pre, int u){
        dfs(pre, u);
        int n = sz[u];
        int c = centroid(pre, u, n);
        pa[c] = (pre ? pre : c);
        for (auto v: a[c]){
            if (pa[v]) continue;
            build(c, v);
        }
    }
    void update(int v){
        for (int u = v;; u = pa[u]){
            ans[u] = min(ans[u], dist(u, v));
            if (u == pa[u]) break;
        }
    }
    int get(int v){
        int res = inf;
        for (int u = v;; u = pa[u]){
            res = min(res, ans[u] + dist(u, v));
            if (u == pa[u]) break;
        }
        return res;
    }
};
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    freopen(".INP", "r", stdin);
    freopen(".OUT", "w", stdout);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    tout[0] = inf;
    dfs(0, 1);
    binlift();
    CD cd(N);
    cd.build(0, 1);
    cd.update(1);
    while (m--){
        int u, v;
        cin >> u >> v;
        if (u == 1) cd.update(v);
        else cout << cd.get(v) << "\n";
    }
}
