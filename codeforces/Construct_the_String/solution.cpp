#include <bits/stdc++.h>

using namespace std;

string pattern(const int sz) {
    string ans(sz, ' ');
    iota(ans.begin(), ans.end(), 'a');
    return ans;
}

string repeat(const string &s, const int times) {
    string ans;
    for (int i = 0; i < times; ++i) ans += s;
    return ans;
}

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        int n, a, b;
        cin >> n >> a >> b;
        
        const int q = n / b;
        const int r = n % b;
        cout << (repeat(pattern(b), q) + pattern(r)) << '\n'; 
    }
    
    cout << endl;

    return 0;
}
