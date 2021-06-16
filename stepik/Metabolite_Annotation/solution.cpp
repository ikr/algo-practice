#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

map<double, int> indices_by_value(const vector<double> &xs) {
    map<double, int> ans;
    for (int i = 0; i < sz(xs); ++i) ans[xs[i]] = i;
    return ans;
}

vector<pii> corresponding_indices(const vector<double> &m,
                                  const vector<double> &a,
                                  const vector<double> &s) {
    const auto idx = indices_by_value(m);
    vector<pii> ans(sz(s), {-1, -1});

    for (int i = 0; i < sz(s); ++i) {
        for (int k = 0; k < sz(a); ++k) {
            const auto it = [&]() {
                const auto lb = idx.lower_bound(max(s[i] - a[k], -a[k]));
                return lb == cend(idx) ? prev(lb) : lb;
            }();

            const auto jt = it == cbegin(idx) ? it : prev(it);

            const auto candidate =
                abs(it->first - s[i] + a[k]) < abs(jt->first - s[i] + a[k])
                    ? pii{it->second, k}
                    : pii{jt->second, k};

            if (ans[i] == pii{-1, -1} ||
                abs(m[candidate.first] + a[candidate.second] - s[i]) <
                    abs(m[ans[i].first] + a[ans[i].second] - s[i])) {
                ans[i] = candidate;
            }
        }
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
