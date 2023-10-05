/*
	Author: Orange
	Problem: https://oj.vnoi.info/problem/mink
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int a[N];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--){
		int n, k;
		cin >> n >> k;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
		}
		deque<int> dq;
		for (int i = 1; i <= n; i++){
			while (dq.size() && a[dq.back()] > a[i]) dq.pop_back();
			dq.push_back(i);
			
			while (dq.size() && dq.front() + k <= i) dq.pop_front();
			if (i >= k) cout << a[dq.front()] << " ";
		}
		cout << "\n";
	}
}
