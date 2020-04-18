#include <bits/stdc++.h>

using namespace std;

optional<string> next_abc(string s) {
    bool carry = true;
    
    for (auto it = s.rbegin(); it != s.rend() && carry; ++it) {
        switch (*it) {
            case 'a':
                *it = 'b';
                carry = false;
                break;
                
            case 'b':
                *it = 'c';
                carry = false;
                break;
                
            case 'c':
                *it = 'a';
                break;
        }
    }
        
    return carry ? nullopt : optional<string>{s};
}

bool is_happy(const string &s) {
    for (int i = 1; i < s.size(); ++i) {
        if (s[i - 1] == s[i]) return false;                          
    }
    
    return true;
}

struct Solution final {
    string getHappyString(int n, int k) const {
        vector<string> ss;
        
        optional<string> curr{string(n, 'a')};
        
        while (!!curr) {
            if (is_happy(*curr)) ss.push_back(*curr);
            curr = next_abc(*curr);
        }
        
        sort(ss.begin(), ss.end());
        
        return k - 1 < ss.size() ? ss[k - 1] : "";
    }
};

int main() {
    const auto actual = Solution{}.getHappyString(3, 9);
    const string expected = "cab";
    
    cout << actual<< endl;
    
    assert(actual == expected);
    
    return 0;
}
