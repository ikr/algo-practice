#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

using ll = long long;

constexpr ll INF = 1e18;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_value(const vector<int> &xs, const int M) {
    const auto N = sz(xs);
    assert(M <= N);

    // D[i][j] — max sought value up to index i on sub-sequences of length j
    vector<vector<ll>> D(N, vector(M + 1, -INF));

    // S[i][j] — sum of elements of xs on which the D[i][j] value is reached
    vector<vector<ll>> S(N, vector(M + 1, 0LL));

    // vector<ll> hi(M + 1, -INF);

    for (int i = 0; i < N; ++i) {
        D[i][0] = 0;
        D[i][1] = xs[i];
        S[i][1] = xs[i];
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= M && i + 1 - j >= 0; ++j) {
            const auto o1 = D[i - 1][j - 1] + 1LL * j * xs[i];

            auto o2 = -INF;
            for (int k = j - 1; k < i; ++k) o2 = max(o2, D[k][j]);

            // const auto o2 = hi[j];

            if (o1 > o2) {
                D[i][j] = o1;
                S[i][j] = S[i - 1][j - 1] + xs[i];
            } else {
                D[i][j] = o2;
                S[i][j] = S[i - 1][j];
            }

            // hi[j] = max(hi[j], D[i][j]);

            // cerr << "i:" << i << " j:" << j << " o1:" << o1 << " o2:" << o2
            //      << " D:" << D[i][j] << " S:" << S[i][j] << endl;
        }
    }

    // cerr << "D:\n" << D << endl;
    // cerr << "S:\n" << S << endl;
    return D.back().back();
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
