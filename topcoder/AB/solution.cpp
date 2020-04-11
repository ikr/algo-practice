#include <bits/stdc++.h>
    
using namespace std;

int largest_divisor(const int x) {
    for (int i = 2; i < sqrt(x) + 1; ++i) {
        if (x % i == 0) return i;
    }
    
    return 1;
}

struct AB final {
    string createString(const int n, const int k) const {
        if (!k) return string('B', n);
        
        const int q = largest_divisor(k);
        const int r = k / q;
     
        if (q + r > n) return "";
        return string(q, 'A') + string(r, 'B') + string(n - q - r, 'A');
    }
};
