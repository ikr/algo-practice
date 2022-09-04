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

    cerr << "D:\n" << D << endl;
    cerr << "S:\n" << S << endl;
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
