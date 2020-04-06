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

string skey(string s) {
    sort(s.begin(), s.end());
    return s;
}

struct Solution final {
    vector<vector<string>> groupAnagrams(const vector<string> &ss) const {
        unordered_multimap<string, string> mm;
        
        for (const auto &s : ss) {
            mm.emplace(skey(s), s);
        }
        
        string last_key = "Z";
        vector<vector<string>> ans;
        
        for (const auto [key, s] : mm) {
            if (last_key != key) {
                ans.emplace_back(vector<string>{});
                last_key = key;
            }
            
            ans.back().emplace_back(s);
        }
        
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    const auto actual = Solution{}.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
    
    cout << actual << endl;
                                                                  
    const vector<vector<string>> expected{
        {"bat"},
        {"nat","tan"},
        {"ate","tea","eat",}
    };
                                                                  
    assert(actual == expected);
    
    return 0;
}
