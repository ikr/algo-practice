#include <array>
#include <iostream>
#include <optional>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

static constexpr int INF = 1e8;
static constexpr int TARGET = 1'000'000;

optional<array<int, 4>> solve(const array<array<int, 4>, 3> &ps) {
    const auto lo = [&]() {
        array<int, 4> xs{INF, INF, INF, INF};

        for (const auto &p : ps) {
            for (int i = 0; i < sz(xs); ++i) {
                xs[i] = min(xs[i], p[i]);
            }
        }

        return xs;
    }();

    int s{};
    array<int, 4> result{};

    for (int i = 0; i < sz(result); ++i) {
        const auto x = min(lo[i], TARGET - s);
        result[i] = x;
        s += x;
    }

    return s == TARGET ? optional{result} : nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        array<array<int, 4>, 3> ps;
        for (auto &p : ps) {
            for (auto &c : p) cin >> c;
        }

        const auto result = solve(ps);
        cout << "Case #" << i << ": ";
        if (result) {
            cout << *result;
        } else {
            cout << "IMPOSSIBLE";
        }
        cout << '\n';
    }

    return 0;
}
