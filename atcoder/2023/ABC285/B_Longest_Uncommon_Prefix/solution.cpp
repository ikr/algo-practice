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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

vector<int> diff(vector<int> xs, const vector<int> &ys) {
    assert(sz(xs) == sz(ys));
    for (int i = 0; i < sz(xs); ++i) {
        xs[i] -= ys[i];
    }
    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    vector<vector<int>> ss(N, vector(AZ, 0));
    ++ss[0][inof(xs[0]) - inof('a')];
    for (int i = 1; i < N; ++i) {
        ss[i] = ss[i - 1];
        const auto j = inof(xs[i]) - inof('a');
        ++ss[i][j];
    }

    cerr << ss << endl;

    vector<int> ans(N - 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        for (int l = 1; i + l < N; ++l) {
            const auto fs = (i ? diff(ss[i + l], ss[i - 1]) : ss[i + l]);
            if (any_of(cbegin(fs), cend(fs),
                       [](const int f) { return f > 1; })) {
                break;
            } else {
                ans[i] = l;
            }
        }
    }

    for (const auto &a : ans) {
        cout << a << '\n';
    }
    return 0;
}
