#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 1;

struct DisjointSet{
    vector<int> parent;
    DisjointSet(int n): parent(n + 1){
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int u){
        if (u != parent[u]) return parent[u] = find(parent[u]);
        return u;
    }

    bool con(int u, int v){
        return find(u) == find(v);	
    }

    bool join(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return false;
        parent[u] = v;
        return true;
    }
};

int n, m;
vector<int> v;

struct query{
    int st, ed, d;
} a[N];

int f(int v, int i){
    return i * N + v;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        string t;
        cin >> a[i].st >> a[i].ed >> t;
        v.push_back(a[i].st);
        v.push_back(a[i].ed);
        a[i].d = (t == "odd");
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    DisjointSet d(N * 2);
    
    for(int i = 1; i <= m; i++){
        a[i].st = lower_bound(v.begin(), v.end(), a[i].st) - v.begin() + 1;
        a[i].ed = lower_bound(v.begin(), v.end(), a[i].ed) - v.begin() + 1;
        
        int &x = a[i].st,
            &y = a[i].ed,
            &m = a[i].d;
        if (m){
            if (d.con(f(x - 1, 0), f(y, 0)) || d.con(f(y, 1), f(x - 1, 1)) || d.con(f(x - 1, 1), f(y, 1)) || d.con(f(y, 0), f(x - 1, 0))){
                return cout << i - 1, 0;
            }
            d.join(f(y, 0), f(x - 1, 1));
            d.join(f(y, 1), f(x - 1, 0));
        }
        else{
            if (d.con(f(x - 1, 1), f(y, 0)) || d.con(f(y, 1), f(x - 1, 0)) || d.con(f(x - 1, 0), f(y, 1)) || d.con(f(y, 0), f(x - 1, 1))){
                 return cout << i - 1, 0;
            }
            d.join(f(y, 0), f(x - 1, 0));
            d.join(f(y, 1), f(x - 1, 1));
        }
    }
    cout << m;
}