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

bool is_compound_word(const unordered_set<string> &dict, const string &w) {
    if (w.empty()) return false;
    const int sz = w.size();
    
    // is words concatenation ending [at index i]
    vector<bool> dp(sz, false);

    for (int i = 0; i != sz; ++i) {
        for (int j = i; j >= -1; --j) {
            if (j == -1) {
                dp[i] = dict.count(w.substr(0, i + 1)); 
            } else {
                if (dp[j] && dict.count(w.substr(j + 1, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }

    return dp[sz - 1];
}

struct Solution final {
    vector<string> findAllConcatenatedWordsInADict(vector<string> ws) const {
        sort(ws.begin(), ws.end(), [](const auto &lhs, const auto &rhs) { return lhs.size() < rhs.size(); });

        unordered_set<string> dict;
        vector<string> ans;

        for (const auto &w : ws) {
            if (is_compound_word(dict, w)) ans.push_back(w);
            dict.insert(w);
        }

        return ans;
    }
};

static const vector<pair<vector<string>, vector<string>>> TCS{
    {
        {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"},
        {"catsdogcats","dogcatsdog","ratcatdogcat"}
    },

    {
        {""},
        {}
    }
};

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    for (const auto [input, expected] : TCS) {
        auto actual = Solution{}.findAllConcatenatedWordsInADict(input);
        sort(actual.begin(), actual.end());

        cout << "EXP " << expected << '\n';
        cout << "ACT " << actual << '\n' << endl;

        assert(actual == expected);
    }

    return 0;
}
