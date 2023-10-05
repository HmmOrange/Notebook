#include <bits/stdc++.h>
#define int long long
using namespace std;
void compare_test(){
    system("g++ -std=c++14 test_gen.cpp -o test_gen");
    system("g++ -std=c++14 good_code.cpp -o good_code");
    system("g++ -std=c++14 bad_code.cpp -o bad_code");
    int cnt = 0;
    while (true){
        system("test_gen.exe > input.txt");

        clock_t start_time = clock();
        system("good_code.exe < input.txt > good_output.txt");
        clock_t end_time = clock();
        long double good_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;

        start_time = clock();
        system("bad_code.exe < input.txt > bad_output.txt");
        end_time = clock();
        long double bad_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;

        system("fc good_output.txt bad_output.txt > test_logger.txt");
        ifstream f("test_logger.txt");
        string s;
        getline(f, s); // skip a line
        f >> s;
        if (s[0] != '*'){
            cout << "Test " << ++cnt << ": WA" << "\n";
            break;
        }
        else cout << "Test " << ++cnt << ": AC (" << bad_duration << "ms - " << good_duration << "ms)" << "\n";
    }
}
void TLE_test(){
    system("g++ -std=c++14 test_gen.cpp -o test_gen");
    system("g++ -std=c++14 good_code.cpp -o good_code");
    system("g++ -std=c++14 bad_code.cpp -o bad_code");
    int cnt = 0;
    while (true){
        system("test_gen.exe > input.txt");

        clock_t start_time = clock();
        system("good_code.exe < input.txt > good_output.txt");
        clock_t end_time = clock();
        long double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;

        ifstream f("test_logger.txt");
        string s;
        getline(f, s); // skip a line
        f >> s;
        if (duration > 1000){
            cout << "Test " << ++cnt << ": TLE (" << duration << "ms)" << "\n";
            break;
        }
        else cout << "Test " << ++cnt << ": AC (" << duration << "ms)" << "\n";
    }
}
signed main(){
    compare_test();
    //TLE_test();
}
