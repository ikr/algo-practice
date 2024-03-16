#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll num_pairs(const ll m) { return m * (m - 1LL) / 2LL; }

ll brute_force(const string &xs) {
    unordered_set<string> seen;
    for (int i = 0; i < sz(xs) - 1; ++i) {
        for (int j = i + 1; j < sz(xs); ++j) {
            auto cur = xs;
            swap(cur[i], cur[j]);
            seen.insert(cur);
        }
    }
    return sz(seen);
}

ll solve(const string &xs) {
    const ll n = sz(xs);
    unordered_map<char, int> fq;
    for (const char x : xs) ++fq[x];
    if (sz(fq) == 1) return 1;

    if (all_of(cbegin(fq), cend(fq),
               [](const auto &p) { return p.second == 1; })) {
        return num_pairs(n);
    }

    ll result = num_pairs(n) + 1;
    for (const auto &[_, f] : fq) {
        if (!f) continue;
        result -= num_pairs(f);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    // if (brute_force(xs) != solve(xs)) {
    //     cerr << "brute_force(xs) = " << brute_force(xs) << endl;
    //     cerr << "solve(xs) = " << solve(xs) << endl;
    // }
    cout << solve(xs) << '\n';
    return 0;
}
