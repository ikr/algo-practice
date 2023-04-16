#include <bits/stdc++.h>
using namespace std;

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

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> struct RndInt final {
    RndInt(const T lo, const T hi) : m_gen{random_device{}()}, m_dist{lo, hi} {}
    T next() { return m_dist(m_gen); }

  private:
    mt19937 m_gen;
    uniform_int_distribution<T> m_dist;
};

vector<int> construct_array(const int N) {
    vector<int> ans;
    ans.reserve(N);
    RndInt rint(0, 1'000'000'000);

    while (sz(ans) < N) {
        ans.push_back(rint.next());
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cerr << setprecision(5) << fixed;

    int N;
    cin >> N;

    const auto xs = construct_array(N);
    assert(sz(xs) == N);
    cout << xs << '\n';

    // set<int> diffs;
    // for (int i = 0; i < N - 1; ++i) {
    //     for (int j = i + 1; j < N; ++j) {
    //         diffs.insert(abs(xs[i] - xs[j]));
    //     }
    // }

    // const auto ps = (1LL * N * (N - 1LL) / 2LL);
    // cerr << "pairs:" << ps << " sz:" << sz(diffs)
    //      << " ratio:" << doof(sz(diffs)) / doof(ps) << '\n';
    return 0;
}
