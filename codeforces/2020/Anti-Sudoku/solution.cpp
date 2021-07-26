#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        vector<string> rows(9, string(9, ' '));
        for (auto &r : rows) { 
            cin >> r;
            
            for (char &c : r) {
                if (c == '9') c = '1';
            }
        }
        
        for (const auto &r : rows) {
            cout << r << '\n';
        }
    }
    
    cout << endl;

    return 0;
}
