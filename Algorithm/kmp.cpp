#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
string p, s;
int n, m;
int t[N];
void kmp(){
	int k = t[1] = 0;
	for (int i = 2; i < n; i++){
		while (k > 0 && s[k + 1] != s[i]) k = t[k];
		if (s[k + 1] == s[i]) k++;
		t[i] = k;
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> p >> s;
	m = p.length();
	s = " " + p + "*" + s;
	n = s.length();
	kmp();
	vector<int> res;
	for (int i = 1; i < n; i++){
		if (t[i] == m) res.push_back(i - 2*m);
	}
	cout << res.size() << "\n";
	for (auto i: res) cout << i << " ";
}

// (๑•ᴗ•๑)っ🍊