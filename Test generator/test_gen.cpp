#include <bits/stdc++.h>
#define int long long
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r){
    return rng() % (r - l + 1) + l;
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n = random(500, 1000);
    int q = random(1, 5000);
    cout << n << " " << q << endl;
    for (int i = 1; i <= n; i++){
        cout << random(-10000, 10000) << " ";
    }
    for (int i = 1; i <= q; i++){
        int l = random(1, n);
        int r = random(l, n);
        cout << l << " " << r << "\n";
    }

}
