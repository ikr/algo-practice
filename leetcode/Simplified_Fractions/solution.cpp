pair<int, int> simplify(const pair<int, int> xy) {
    const auto [x, y] = xy;
    const int g = gcd(x, y);
    return {x / g, y / g};
}

string frac(const int x, const int y) {
    stringstream ss;
    ss << x << "/" << y;
    return ss.str();
}

class Solution {
public:
    vector<string> simplifiedFractions(const int n) {
        set<pair<int, int>> xys;
        
        for (int de = 2; de <= n; ++de) {
            for (int nu = 1; nu < de; ++nu) {
                xys.insert(simplify({nu, de}));
            }
        }
        
        vector<string> ans;
        for (const auto xy : xys) {
            const auto [x, y] = xy;
            ans.push_back(frac(x, y));
        }
        return ans;
    }
};
