#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i != t; ++i) {
        int n;
        cin >> n;
        
        cout << (n % 2 ? n / 2 : n / 2 - 1) << "\n";    
    }
    
    cout << endl;

    return 0;
}
