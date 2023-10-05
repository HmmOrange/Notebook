/*
	Date: 12/7/2022
	Problem: Matrix Multiplication (Fibonacci)
	Author: Orange 🍊
	
	Template source: VNOI wiki
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int BASE_DIGITS = 9;
const int BASE = 1000000000;

using type = int; // Kiểu dữ liệu các phần tử của ma trận 

struct Matrix {
    vector <vector <type> > data;

    // Số lượng hàng của ma trận
    int row() const { return data.size(); } 

    // Số lượng hàng của ma trận
    int col() const { return data[0].size(); }

    auto & operator [] (int i) { return data[i]; }
    
    const auto & operator[] (int i) const { return data[i]; }

    Matrix() = default;
    
    Matrix(int r, int c): data(r, vector <type> (c)) { }

    Matrix(const vector <vector <type> > &d): data(d) {

        // Kiểm tra các hàng có cùng size không và size có lớn hơn 0 hay không
        // Tuy nhiên không thực sự cần thiết, ta có thể bỏ các dòng /**/ đi
        /**/ assert(d.size());
        /**/ int size = d[0].size();
        /**/ assert(size);
        /**/ for (auto x : d) assert(x.size() == size);
    }

    // In ra ma trận.
    friend ostream & operator << (ostream &out, const Matrix &d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }

    // Ma trận đơn vị
    static Matrix identity(long long n) {
        Matrix a = Matrix(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }

    // Nhân ma trận
    Matrix operator * (const Matrix &b) {
        Matrix a = *this;

        // Kiểm tra điều kiện nhân ma trận
        assert(a.col() == b.row()); 

        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k)
                    c[i][j] += a[i][k] * b[k][j];
        return c;
    }

    // Lũy thừa ma trận
    Matrix pow(long long exp) {

        // Kiểm tra điều kiện lũy thừa ma trận (là ma trận vuông)
        assert(row() == col());  

        Matrix base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	Matrix a(2, 2);
	a[0][0] = 0;
	a[0][1] = 1;
	a[1][0] = 1;
	a[1][1] = 1;
	Matrix b(2, 1);
	b[0][0] = 1;
	b[1][0] = 2;
	Matrix c = a.pow(n - 1)*b;
	cout << c[1][0] << "\n";
}

// (๑•ᴗ•๑)っ🍊