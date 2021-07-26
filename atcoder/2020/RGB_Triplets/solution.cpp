#include <bits/stdc++.h>

using namespace std;

using Int = long long;

map<char, set<Int>> gather_indices_by_color(const string &s) {
    map<char, set<Int>> ans{{'R', {}}, {'G', {}}, {'B', {}}};

    for (Int i = 0; i != s.size(); ++i) {
        ans[s[i]].insert(i);
    }

    return ans;
}

vector<tuple<char, char, char>> all_triples() {
    vector<tuple<char, char, char>> ans;
    vector<char> curr{'B', 'G', 'R'};

    do {
        ans.emplace_back(curr[0], curr[1], curr[2]);
    } while (next_permutation(curr.begin(), curr.end()));

    return ans;
}

Int count_isooffsets(const map<char, set<Int>> &indices_by_color) {
    Int ans = 0;

    for (const auto [c1, c2, c3] : all_triples()) {
        for (auto i : indices_by_color.at(c1)) {
            for (
                auto itk = indices_by_color.at(c3).upper_bound(i); 
                itk != indices_by_color.at(c3).cend();
                ++itk
            ) {
                const auto k = *itk;
                if ((k - i) % 2) continue;
                if (indices_by_color.at(c2).count(i + (k - i) / 2)) ++ans;
            }
        } 
    }

    return ans;
}

int main() {
    Int n;
    string s;
    cin >> n >> s;

    const auto indices_by_color = gather_indices_by_color(s);

    const Int ans = accumulate(
        indices_by_color.cbegin(), 
        indices_by_color.cend(), 
        1LL, 
        [](const Int memo, const auto p) { return memo * p.second.size(); }
    ) - count_isooffsets(indices_by_color);

    cout << ans << endl;

    return 0;
}
