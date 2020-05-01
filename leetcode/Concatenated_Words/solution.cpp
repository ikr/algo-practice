#include <bits/stdc++.h>

using namespace std;

bool is_compound_word(const unordered_set<string> &dict, const string &w) {
    const int sz = w.size();
    
    for (int l = 1; l <= sz; ++l) {
        if (dict.count(w.substr(0, l))) return l == sz ? true : is_compound_word(dict, w.substr(l));
    }

    return false;
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

int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    const vector<string> input{"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"};
    const vector<string> expected{"catsdogcats","dogcatsdog","ratcatdogcat"};
    const auto actual = Solution{}.findAllConcatenatedWordsInADict(input);

    assert(actual == expected);

    return 0;
}
