#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

map<double, pii> indices_by_sum(const vector<double> &m,
                                const vector<double> &a) {
    map<double, pii> ans;

    for (int j = 0; j < sz(m); ++j) {
        for (int k = 0; k < sz(a); ++k) {
            if (m[j] + a[k] <= 0) continue;
            ans[m[j] + a[k]] = pii{j, k};
        }
    }

    return ans;
}

vector<pii> corresponding_indices(const vector<double> &m,
                                  const vector<double> &a,
                                  const vector<double> &s) {
    const auto idx = indices_by_sum(m, a);
    vector<pii> ans(sz(s), {-1, -1});

    for (int i = 0; i < sz(s); ++i) {
        auto it = idx.lower_bound(s[i]);
        if (it == cend(idx)) it = prev(cend(idx));

        const auto jt = it == cbegin(idx) ? it : prev(it);
        ans[i] = abs(it->first - s[i]) < abs(jt->first - s[i]) ? it->second
                                                               : jt->second;
    }

    return ans;
}

void print_answer(const vector<pii> &ans) {
    for (const auto [j, k] : ans) {
        cout << j + 1 << ' ' << k + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int M, K, N;
        cin >> M >> K >> N;

        vector<double> m(M);
        for (auto &x : m) cin >> x;

        vector<double> a(K);
        for (auto &x : a) cin >> x;

        vector<double> s(N);
        for (auto &x : s) cin >> x;

        print_answer(corresponding_indices(m, a, s));
    }

    return 0;
}
