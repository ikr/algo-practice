#include <bits/stdc++.h>

using namespace std;

using Int = long long;

Int kth_lunlun(const int k) {
    if (k < 10) return k;
    
    queue<Int> q;
    for (int i = 1; i != 10; ++i) {
        q.push(i);
    }
    
    Int ans = -1;
    
    for (int i = 1; i <= k; ++i) {
        const Int x = q.front();
        q.pop();
        const Int last_digit = x % 10;
        
        if (last_digit) q.push(10 * x + last_digit - 1);
        q.push(10 * x + last_digit);
        if (last_digit != 9) q.push(10 * x + last_digit + 1);
        
        ans = x;
    }
    
    return ans;
}   

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int k;
    cin >> k;
    cout << kth_lunlun(k) << endl;
}
