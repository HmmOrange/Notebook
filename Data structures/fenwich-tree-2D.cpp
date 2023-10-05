#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 505;
const int inf = 1e18;

int bit[N][N];
int m, n, q;
int get(int x, int y){
	int res = 0;
	for (int i = x; i >= 1; i -= (i & -i)){
		for (int j = y; j >= 1; j -= (j & -j)){
			res += bit[i][j];
		}
	}
	return res;
}

void update(int x, int y, int v){
	for (int i = x; i < N; i += (i & -i)){
		for (int j = y; j < N; j += (j & -j)){
			bit[i][j] += v;
			//cout << i << " " << j << endl;
		}
	}
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> m >> n >> q;
	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			cin >> a[i][j];
		}
	}
	while (q--){
		int type, x, y, u, v, w;
		cin >> type;
		if (type == 1){
			cin >> x >> y >> u >> v >> w;
			update(u, v, w);
			if (x > 1) update(x - 1, v, -w);
			if (y > 1) update(u, y - 1, -w);
			if (x > 1 && y > 1) update(x - 1, y - 1, w);
		}
		else{
			cin >> x >> y >> u >> v;
			cout << get(u, v) - get(x - 1, v) - get(u, y - 1) + get(x - 1, y - 1) << "\n";
		}
	}
}

