#include <bits/stdc++.h>
    
using namespace std;
    
int main() {    
    int n;
    cin >> n;
    
    bool yes = false;
    while (n) {
        if (n % 10 == 7) {
            yes = true;
            break;
        }
        
        n /= 10;
    }
    
    cout << (yes ? "Yes" : "No") << endl;
    
    return 0;
}
