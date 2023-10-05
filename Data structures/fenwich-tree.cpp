#include <bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;

int a[N];
int bit[N];
int n;

struct FenwichTree{
    vector<int> bit;
    FenwichTree(int n): bit(n + 1){
        for (int i = 1; i <= n; i++) bit[i] = 0;
    }
	
	int get(int x){
		int bruh = 0;
		for (int i = x; i >= 1; i -= (i & -i)){
			bruh += bit[i];
		}
		return bruh;
	}
	
	void update(int u, int v){
		for (int i = u; i <= n; i += (i & -i)){
			bit[i] += v;
		}
	}
};

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		update(i, i);
	}
	deque<int> f;
	
	for (int i = 1; i <= n; i++){
		cout << "!!!" << i << "#" << bit[i] << " ";
	}
	cout << endl;
	//cout << bit[1] << endl;
	for (int i = n; i >= 1; i--){
		int s = 0, k = 0;
		for (int j = 30; j >= 0; j--){
			if (k + (1 << j) <= n) cout << i << "#" << j << " " << s << " " << bit[k + (1 << j)] << endl;
			if ((k + (1 << j) <= n) && (s + bit[k + (1 << j)] <= a[i])){
				k += (1 << j);
				s += bit[k];
				cout << s << " " << k << endl;
			}
		}
		k++;
		f.push_back(k);
		update(k, -k);
		for (int i = 1; i <= n; i++){
			cout << "!!!" << i << "#" << bit[i] << " ";
		}
		cout << endl;
	}
	while (f.size()){
		cout << f.back() << " ";
		f.pop_back();
	}
}