#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_value(const vector<int> &xs, const int M) {
    const auto N = sz(xs);
    assert(M <= N);

    ll t{};
    ll s{};
    for (int i = 1; i <= M; ++i) {
        t += xs[i - 1];
        s += 1LL * i * xs[i - 1];
    }

    auto result = s;
    // cerr << "s0:" << s << endl;

    for (int d = 1; d <= N - M; ++d) {
        const int i = d;
        t -= xs[i - 1];
        s -= xs[i - 1];

        const int j = M + d;
        s += 1LL * M * xs[j - 1];
        s -= t;
        t += xs[j - 1];

        // cerr << "t:" << t << " s:" << s << endl;
        result = max(result, s);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_value(xs, M) << '\n';
    return 0;
}
