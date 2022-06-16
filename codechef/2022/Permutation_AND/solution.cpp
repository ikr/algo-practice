#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << " : " << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vector<int>, vector<int>> two_perms(const int N) {
    if (N == 1) return pair{vector<int>{1}, vector<int>{1}};
    if (N % 2) return pair{vector<int>{}, vector<int>{}};

    vector<int> xs(N);
    iota(begin(xs), end(xs), 1);

    auto ys = xs;
    reverse(begin(ys), end(ys));

    const auto edge = [&]() -> int {
        if ((N & 1) == (2 & (N - 1))) return 0;

        for (int i = 1; i < N; ++i) {
            if ((N & (i + 1)) == (1 & i)) {
                return N - i;
            }
        }

        assert(false && "/o\\");
        return -1;
    }();

    rotate(begin(ys), next(begin(ys), edge), end(ys));

    const auto t = xs[0] & ys[0];
    for (int i = 1; i < sz(xs); ++i) {
        assert((xs[i] & ys[i]) == t);
    }

    return {xs, ys};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        const auto [xs, ys] = two_perms(N);
        if (xs.empty()) {
            cout << "-1\n";
        } else {
            cout << xs << '\n' << ys << '\n';
        }
    }

    return 0;
}
