#include <bits/stdc++.h>

using namespace std;

vector<string> grow_happiness(const vector<string> &ss) {
    vector<string> ans;
    
    for (const auto &s : ss) {
        for (const char c : {'a', 'b', 'c'}) {
            if (s.back() != c) {
                string nova = s;
                nova += c;
                ans.push_back(nova);
            }
        }
    }
    
    return ans;
}

struct Solution final {
    string getHappyString(int n, int k) const {
        vector<string> ss{"a", "b", "c"};
        
        while (ss.front().size() < n) {
            ss = grow_happiness(ss);
        }
        
        sort(ss.begin(), ss.end());
        return k - 1 < ss.size() ? ss[k - 1] : "";
    }
};

int main() {
    const auto actual = Solution{}.getHappyString(3, 9);
    const string expected = "cab";
    
    cout << "ACT " << actual<< endl;
    cout << "EXP " << expected << endl;
    
    assert(actual == expected);
    
    return 0;
}
