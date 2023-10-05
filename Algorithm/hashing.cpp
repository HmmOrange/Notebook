#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
const int N = 2e3 + 5;
int gud[N];
pii h[N], p_pow[N];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	s = "*" + s;
	
	string bit01;
	cin >> bit01;
	for (int i = 0; i < 26; i++){
		gud['a' + i] = (bit01[i] == '1');
	}
	gud['*'] = 1;
	int k;
	cin >> k;
	
	int m1 = 1e9 + 9, m2 = 1e9 + 7;
	int p1 = 31, p2 = 37;
	p_pow[0] = {1, 1};
	
	for (int i = 1; i < N; i++){
		p_pow[i].first = (p_pow[i - 1].first * p1) % m1;
		p_pow[i].second = (p_pow[i - 1].second * p2) % m2;
	}
	
	for (int i = 1; i < s.length(); i++){
		h[i].first = (h[i - 1].first + (s[i] - 'a' + 1) * p_pow[i].first) % m1;
		h[i].second = (h[i - 1].second + (s[i] - 'a' + 1) * p_pow[i].second) % m2;
		//cout << i << " " << h[i] << " " << p_pow[i] << endl;
	}
	
	set<pii> diff_hash;
	for (int l = 1; l <= s.length(); l++){
		int bad_cnt = 0;
		for (int i = 1; i < l; i++){
			if (!gud[s[i]]) bad_cnt++;
		}
		for (int i = 1; i + l - 1 < s.length(); i++){
			if (!gud[s[i + l - 1]]) bad_cnt++;
			if (!gud[s[i - 1]]) bad_cnt--; 
			
			if (bad_cnt <= k){
				int f1 = (h[i + l - 1].first - h[i - 1].first + m1) % m1;
				f1 = (f1 * p_pow[s.length() - (i - 1)].first) % m1;
				int f2 = (h[i + l - 1].second - h[i - 1].second + m2) % m2;
				f2 = (f2 * p_pow[s.length() - (i - 1)].second) % m2;
				diff_hash.insert({f1, f2});
			}
		}
	}
	cout << diff_hash.size() << "\n";
	
	
}

// (๑•ᴗ•๑)っ🍊