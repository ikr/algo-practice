#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

struct Solution final {
    int countElements(const vector<int> &xs) const {
        vector<bool> seen(1001, false);
        
        for (const int x : xs) {
            seen[x] = true;
        }
        
        int ans = 0;
        
        for (const int x : xs) {
            if (seen[x + 1]) ++ans;
        }
        
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    const auto actual = Solution{}.countElements({1,1,2,2});          
    const int expected = 2;
    
    cout << "actual is " << actual << " expected is " << expected << endl;
            
    assert(actual == expected);
    
    return 0;
}
