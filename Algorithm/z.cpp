#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;

string P, T, s;
int z[N], n;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
    cin >> P >> T;
    n = P.length();
    s = " " + P + "*" + T; // đánh số từ 1

    z[1] = 0;
    int m = s.length();
    int l = 0, r = 0;
    for (int k = 2; k < m; k++){
        int x = 0;
        if (k <= r) x = min(z[k - l + 1], r - k + 1);
        while (k + x < m && s[x + 1] == s[k + x]) x++;
        z[k] = x;
        if (r < k + z[k] - 1){
            l = k;
            r = k + z[k] - 1;
        }
    }

    vector<int> res;
    for (int i = n + 2; i < m; i++)
        if (z[i] == n) res.push_back(i - n - 1);
    cout << res.size() << "\n";
    for (int x: res) cout << x << " ";
}

