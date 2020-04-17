#include <bits/stdc++.h>

using namespace std;

template <typename K, typename V>
ostream &operator<<(ostream &os, const multimap<K, V> &m) {
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '{' << i->first << ' ' << i->second << '}';
    }

    return os;
}

using Int = long long;

multimap<char, Int> gather_indices_by_color(const string &s) {
    multimap<char, Int> ans;

    for (Int i = 0; i != s.size(); ++i) {
        ans.emplace(s[i], i);
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

Int count_isooffsets(const multimap<char, Int> &indices_by_color) {
    Int ans = 0;

    for (const auto [c1, c2, c3] : all_triples()) {
    }

    return ans;
}

int main() {
    assert(all_triples().size() == 6);

    Int n;
    string s;
    cin >> n >> s;

    auto indices_by_color = gather_indices_by_color(s);

    cout << indices_by_color << endl;
    cout << indices_by_color.count('R') * indices_by_color.count('G') * indices_by_color.count('B') << endl;
    cout << count_isooffsets(indices_by_color) << endl;

    const Int ans = 
        indices_by_color.count('R') * indices_by_color.count('G') * indices_by_color.count('B')
            - count_isooffsets(indices_by_color);
    
    cout << ans << endl;
}
