#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const vector<pair<T1, T2>> &xs) {
    os << sz(xs) << '\n';
    for (const auto &[a, b] : xs) {
        cout << a << ' ' << b << '\n';
    }
    return os;
}

template <typename T> struct RndInt final {
    RndInt(const T lo, const T hi) : m_gen{random_device{}()}, m_dist{lo, hi} {}
    T next() { return m_dist(m_gen); }

  private:
    mt19937 m_gen;
    uniform_int_distribution<T> m_dist;
};

vector<pii> random_pairs(const int n) {
    vector<pii> result(n);
    RndInt rnd(0, 3000);
    for (int i = 0; i < n; ++i) {
        result[i] = pii{rnd.next(), rnd.next()};
    }
    return result;
}

int main() {
    const int T = 3;
    const int HI = 500000;
    cout << T << "\n\n";

    for (int i = 1; i <= T; ++i) {
        cout << random_pairs(HI) << '\n' << random_pairs(HI) << '\n';
    }

    return 0;
}
