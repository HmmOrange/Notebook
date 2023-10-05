//convex-hull
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct pt{ // Kiểu điểm
  	double x, y;
  	double angle;
};

bool cmp(pt a, pt b) { // So sánh theo tọa độ x, trong trường hợp bằng nhau so sánh theo y
  	return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(pt a, pt b, pt c) { // a -> b -> c đi theo thứ tự xuôi chiều kim đồng hồ
  	return !(a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0);
}

bool ccw(pt a, pt b, pt c) { // a -> b -> c đi theo thứ tự ngược chiều kim đồng hồ
  	return !(a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0);
}

void convex_hull (vector<pt> &a) {
  	if (a.size() == 1) { // chỉ có 1 điểm
    	return;
  	}

  	// Sắp xếp các điểm theo tọa độ x, nếu bằng nhau sắp xếp theo y
  	sort (a.begin(), a.end(), &cmp);
	
  	pt p1 = a[0], p2 = a.back();

  	vector<pt> up, down; // chuỗi trên và chuỗi dưới
  	up.push_back(p1);
  	down.push_back(p1);

  	for (size_t i = 1; i < a.size(); i++) { // xét lần lượt các điểm
    // Thêm vào chuỗi trên
	    if (i == a.size()-1 || cw(p1, a[i], p2)) {
	      	while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
	        	up.pop_back();
	      	up.push_back(a[i]);
		}
	
	    // Thêm vào chuỗi dưới
	    if (i == a.size()-1 || ccw(p1, a[i], p2)) {
	      	while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
	    		down.pop_back();
	      	down.push_back(a[i]);
	    }
  	}

  // Gộp 2 chuỗi trên và dưới để lấy bao lồi
  	a.clear();
  	for (size_t i = 0; i < up.size(); i++)
    	a.push_back(up[i]);
  	for (size_t i = down.size() - 2; i > 0; i--)
    	a.push_back(down[i]);
}
double dist(pt a, pt b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	vector<pt> ptf;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		pt f;
		cin >> f.x >> f.y;
		ptf.push_back(f);
	}
	convex_hull(ptf);
	cout << ptf.size() << endl;
	for (auto i: ptf) cout << (int)i.x << " " << (int)i.y << endl;
	
}