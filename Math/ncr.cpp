//nCr
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;
int fac[N];
int x, y;
int power(int x, int n){
    int res = 1;
    while (n){
        if (n & 1) (res *= x) %= MOD;
        (x *= x) %= MOD;
        n >>= 1;
    }
    return res;
}
 
 
int modInverse(int n){
    return power(n, MOD - 2);
}
 
int nCr(int n, int r){
    if (n < r)
        return 0;
    if (r == 0)
        return 1;
    return (fac[n] * modInverse(fac[r]) % MOD) * modInverse(fac[n - r]) % MOD;
}
 
void preCompute(){
    fac[0] = 1;
    for (int i = 1; i < N; i++)
        fac[i] = (fac[i - 1] * i) % MOD;
}
 
signed main(){
	int n;
	cin >> n;
	preCompute();
	int s = 0;
	for (int i = 1; i <= 1; i++){
		s += nCr(4, 2);
	}
	cout << s << endl;
}