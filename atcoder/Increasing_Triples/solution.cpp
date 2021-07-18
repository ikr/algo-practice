#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_proper_triples_num(multiset<int> a, multiset<int> b, multiset<int> c) {
    int ans = 0;

    for (const auto x : a) {
        const auto it = b.upper_bound(x);
        if (it == cend(b)) continue;

        const auto jt = c.upper_bound(*it);
        if (jt == cend(c)) continue;

        ++ans;
        b.erase(it);
        c.erase(jt);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    array<multiset<int>, 3> abc;
    for (auto &xs : abc) {
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            xs.insert(x);
        }
    }

    cout << max_proper_triples_num(move(abc[0]), move(abc[1]), move(abc[2]))
         << '\n';
    return 0;
}
