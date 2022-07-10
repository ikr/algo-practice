#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
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

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<set<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, vector<int>> indices_by_value(const vector<int> &xs) {
    map<int, vector<int>> result;
    for (int i = 0; i < sz(xs); ++i) {
        result[xs[i]].push_back(i);
    }
    return result;
}

vector<int> indices_of_powers_of_two(const vector<int> &xs) {
    vector<int> result;
    for (int i = 0; i < sz(xs); ++i) {
        if (__builtin_popcount(xs[i]) == 1) result.push_back(i);
    }
    return result;
}

vector<set<int>> ys_options(const vector<int> &xs, const vector<int> &ys) {
    const auto n = sz(ys);
    const auto idx = indices_by_value(xs);
    const auto two = indices_of_powers_of_two(xs);
    vector<set<int>> result(n, set<int>(cbegin(two), cend(two)));

    for (int i = 0; i < n; ++i) {
        const auto y = ys[i];
        if (idx.count(y)) {
            result[i].insert(cbegin(idx.at(y)), cend(idx.at(y)));
        }

        {
            ll yy = y;
            while (yy / 2LL >= 1L) {
                yy /= 2L;
                if (idx.count(inof(yy))) {
                    result[i].insert(cbegin(idx.at(inof(yy))),
                                     cend(idx.at(inof(yy))));
                }
            }
        }

        {
            ll yy = y;
            while (yy * 2LL <= 1'000'000'000) {
                yy *= 2L;
                if (idx.count(inof(yy))) {
                    result[i].insert(cbegin(idx.at(inof(yy))),
                                     cend(idx.at(inof(yy))));
                }
            }
        }
    }

    return result;
}

bool is_possible(const vector<int> &xs, const vector<int> &ys) {
    auto opts = ys_options(xs, ys);

    if (any_of(cbegin(opts), cend(opts),
               [](const auto &opt) { return opt.empty(); })) {
        return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ys(n);
        for (auto &y : ys) cin >> y;

        cout << (is_possible(xs, ys) ? "YES" : "NO") << '\n';
    }

    return 0;
}
