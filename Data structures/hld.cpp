/*
	Author: Orange
	Problem: https://www.spoj.com/problems/QTREE/
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int N = 1e4 + 5;
const int K = 15;
const int inf = 1e9;

//Tree
int n;
vector<int> a[N];
struct Edge{
	int u; int v; int t;
} edge[N];

int subCnt[N], parent[N], tin[N], tout[N];
int ttime = 0;
void tree(int pre, int u){
	parent[u] = pre;
	tin[u] = ++ttime;
	subCnt[u] = 1;
	for (auto v: a[u]){
		if (v == pre) continue;
		tree(u, v);
		subCnt[u] += subCnt[v];
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

//Segment Tree
int st[4*N + 5];
void update(int id, int l, int r, int i, int v){
	if (i < l || r < i) return;
	if (l == r){
		st[id] = v;
		return;
	}
	int mid = (l + r) >> 1;
	update(id*2, l, mid, i, v);
	update(id*2 + 1, mid + 1, r, i, v);

	st[id] = max(st[id << 1], st[id << 1 | 1]);
}

int get(int id, int l, int r, int u, int v){
	if (v < l || r < u) return -inf;
	if (u <= l && r <= v){
		return st[id];
	}
	int mid = (l + r) >> 1;
	return max(get(id << 1, l, mid, u, v),
	           get(id << 1 | 1, mid + 1, r, u, v));

}

//HLD
int chainCnt = 0, vtxCnt = 0;
int chainHead[N], chainInd[N], vtxPos[N];

void hld(int pre, int u){
	if (chainHead[chainCnt] == 0)
		chainHead[chainCnt] = u;
	chainInd[u] = chainCnt;
	vtxPos[u] = ++vtxCnt;
	int vtxf = -1;
	for (auto v: a[u]){
		if (v == pre) continue;
		if (vtxf == -1 || subCnt[vtxf] < subCnt[v])
			vtxf = v;
	}
	if (vtxf > -1) hld(u, vtxf);
	for (auto v: a[u]){
		if (v == pre || v == vtxf) continue;
		chainCnt++;
		hld(u, v);
	}
}

int query(int u, int a){
	int res = -inf;
	int uchain = chainInd[u];
	int achain = chainInd[a];
	while (true){
		//cerr << uchain << " " << achain << "#" << u << " " << a << "#" << vtxPos[chainHead[uchain]] << " " << vtxPos[u] << "-->" << res << "\n";
		if (uchain == achain){
			res = max(res, get(1, 1, n, vtxPos[a] + 1, vtxPos[u]));
			break;
		}
		res = max(res, get(1, 1, n, vtxPos[chainHead[uchain]], vtxPos[u]));
		u = parent[chainHead[uchain]];
        uchain = chainInd[u];
	}
	return res;
}
signed main(){
    //freopen("bruh.inp", "r", stdin);
    //freopen("bruh.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--){
		cin >> n;
		//Init
		chainCnt = 1, vtxCnt = 0;
		memset(chainHead, 0, sizeof chainHead);
		//memset(chainInd, 0, sizeof chainInd);
		//memset(vtxPos, 0, sizeof vtxPos);
		//memset(subCnt, 0, sizeof subCnt);
		memset(st, 0, sizeof st);
		//memset(p, 0, sizeof p);

		parent[1] = 0;
		tout[0] = 1e9;
		ttime = 0;
		for (int i = 1; i <= n; i++){
			a[i].clear();
		}
		//Solve
		for (int i = 1, u, v, t; i < n; i++){
			cin >> u >> v >> t;
			a[u].push_back(v);
			a[v].push_back(u);
			edge[i] = (Edge){u, v, t};
		}
		//cerr << "0" << "\n";
		tree(0, 1);
		//cerr << "1" << "\n";
		binlift();
		//cerr << "2" << "\n";
		hld(0, 1);
		//cerr << "3" << "\n";
		//cerr << chainInd[10000] << "\n";

		//Checking paths
		for (int i = 1; i < n; i++){
			if (ancestor(edge[i].v, edge[i].u)) swap(edge[i].u, edge[i].v);
		}
		string qs;
		for (int i = 1; i < n; i++){
			update(1, 1, n, vtxPos[edge[i].v], edge[i].t);
		}
		while (cin >> qs && qs[0] != 'D'){
			//cerr << "4" << "\n";
			int u, v;
			cin >> u >> v;

			//cerr << qs << " " << u << " " << v << "\n";
			if (qs[0] != 'Q'){
				update(1, 1, n, vtxPos[edge[u].v], v);
				//cerr << "5" << "\n";
			}
			else{
				int f = lca(u, v);
				//cerr << "6" << "#" << f << "\n";
				cout << max(query(u, f), query(v, f)) << "\n";
				//cerr << "7" << "\n";
			}
		}
	}
}
