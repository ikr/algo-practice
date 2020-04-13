#include <bits/stdc++.h>

using namespace std;

template <typename K, typename V>
ostream &operator<<(ostream &os, const unordered_multimap<K, V> &m) {
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '{' << i->first << ' ' << i->second << '}';
    }

    return os;
}

using Int = long long;

unordered_multimap<char, Int> gather_indices_by_color(const string &s) {
    unordered_multimap<char, Int> ans;

    for (Int i = 0; i != s.size(); ++i) {
        ans.emplace(s[i], i);
    }

    return ans;
}

string color_pair_key(const char c1, const char c2) {
    string ans{c1, c2};
    sort(ans.begin(), ans.end());
    return ans;
}

map<string, unordered_map<Int, Int>>
gather_counts_by_offset_by_color_pair_key(const unordered_multimap<char, Int> &indices_by_color) {
    map<string, unordered_map<Int, Int>> ans;

    for (const auto [c1, c2] : vector<pair<char, char>>{{'R', 'G'}, {'G', 'B'}, {'R', 'B'}}) {
        const auto key = color_pair_key(c1, c2);
        ans[key] = {};

        const auto [ifirst, ilast] = indices_by_color.equal_range(c1);
        for (auto it = ifirst; it != ilast; ++it) {
            const auto [jfirst, jlast] = indices_by_color.equal_range(c2);
            for (auto jt = jfirst; jt != jlast; ++jt) {
                ans[key][abs(it->second - jt->second)]++;
            }
        }
    }

    return ans;
}

Int count_isooffsets(const unordered_multimap<char, Int> &indices_by_color) {
    auto counts_by_offset_by_color_pair_key = gather_counts_by_offset_by_color_pair_key(indices_by_color);
    Int ans = 0;

    for (const auto [c1, c2, c3] : vector<array<char, 3>>{{'G', 'R', 'B'}, {'R', 'G', 'B'}, {'R', 'B', 'G'}}) {
        const auto key = color_pair_key(c2, c3);

        const auto [ifirst, ilast] = indices_by_color.equal_range(c1);
        for (auto it = ifirst; it != ilast; ++it) {
            const auto [jfirst, jlast] = indices_by_color.equal_range(c2);
            for (auto jt = jfirst; jt != jlast; ++jt) {
                const Int offset = abs(it->second - jt->second);
                ans += counts_by_offset_by_color_pair_key[key][offset];
            }
        }
    }

    return ans;
}

int main() {
    Int n;
    string s;
    cin >> n >> s;

    auto indices_by_color = gather_indices_by_color(s);

    cout << indices_by_color << endl;
    cout << count_isooffsets(indices_by_color) << endl;

    const Int ans = 
        indices_by_color.count('R') * indices_by_color.count('G') * indices_by_color.count('B')
            - count_isooffsets(indices_by_color);
    
    cout << ans << endl;
}
