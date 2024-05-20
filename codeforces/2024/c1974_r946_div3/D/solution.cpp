#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char opposite(const char x) {
    switch (x) {
    case 'N':
        return 'S';
    case 'S':
        return 'N';
    case 'E':
        return 'W';
    default:
        assert(x == 'W');
        return 'E';
    }
}

optional<string> vehicle_assignments(const string &xs) {
    map<char, int> fq;
    map<char, vector<int>> idx;
    for (int i = 0; i < sz(xs); ++i) {
        ++fq[xs[i]];
        idx[xs[i]].push_back(i);
    }

    vector<int> rs;
    vector<int> hs;

    for (const auto d : {'N', 'S', 'W', 'E'}) {
        const auto f = fq[d];
        const auto m = f / 2;
        for (int j = 0; j < m; ++j) {
            rs.push_back(idx[d].back());
            idx[d].pop_back();

            hs.push_back(idx[d].back());
            idx[d].pop_back();
        }
        fq[d] -= 2 * m;
    }
    for (const auto d : {'N', 'S', 'W', 'E'}) {
        if (fq[d]) {
            assert(fq[d] == 1);
            if (fq[d] != fq[opposite(d)]) return nullopt;

            auto &target = sz(rs) <= sz(hs) ? rs : hs;

            target.push_back(idx[d].back());
            idx[d].pop_back();
            target.push_back(idx[opposite(d)].back());
            idx[opposite(d)].pop_back();
            --fq[d];
            --fq[opposite(d)];
        }
    }

    if (empty(rs) || empty(hs)) return nullopt;

    string result(sz(xs), ' ');
    for (const auto i : rs) result[i] = 'R';
    for (const auto i : hs) result[i] = 'H';
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        const auto result = vehicle_assignments(xs);
        cout << (result ? *result : string{"NO"}) << '\n';
    }

    return 0;
}
