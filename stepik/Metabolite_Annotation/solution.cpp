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

vector<pii> corresponding_indices(const vector<double> &m,
                                  const vector<double> &a,
                                  const vector<double> &s) {
    vector<pii> ans(sz(s), {-1, -1});

    for (int i = 0; i < sz(s); ++i) {
        double best_err = 1e6;

        for (int j = 0; j < sz(m); ++j) {
            for (int k = 0; k < sz(a); ++k) {
                if (m[j] + a[k] <= 0) continue;

                const auto err = abs(m[j] + a[k] - s[i]);
                if (err < best_err) {
                    best_err = err;
                    ans[i] = pii{j, k};
                }
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
