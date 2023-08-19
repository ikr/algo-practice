#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pii> fss(N);
    for (auto &[f, s] : fss) {
        cin >> f >> s;
        --f;
    }

    vector<int> hi_by_f(N, 0);
    vector<multiset<int>> by_f(N);

    for (const auto &[f, s] : fss) {
        hi_by_f[f] = max(hi_by_f[f], s);
        by_f[f].insert(s);
    }

    sort(rbegin(hi_by_f), rend(hi_by_f));
    ll ans{};
    if (hi_by_f[0] && hi_by_f[1]) ans = hi_by_f[0] + hi_by_f[1];

    for (const auto &ss : by_f) {
        if (sz(ss) < 2) continue;
        const auto a = *prev(cend(ss));
        const auto b = *prev(prev(cend(ss)));
        ans = max(ans, a + 0LL + b / 2);
    }

    cout << ans << '\n';
    return 0;
}
