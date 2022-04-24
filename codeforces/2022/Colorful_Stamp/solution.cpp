#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pair<char, int>> encode(const string &xs) {
    vector<pair<char, int>> result{{xs[0], 1}};

    for (int i = 1; i < sz(xs); ++i) {
        auto &[c, l] = result.back();

        if (xs[i] == c) {
            ++l;
        } else {
            result.emplace_back(xs[i], 1);
        }
    }

    return result;
}

char peer(const char x) { return x == 'R' ? 'B' : 'R'; }

bool is_possible(const string &xs) {
    const auto ys = encode(xs);

    for (int i = 0; i < sz(ys); ++i) {
        if (ys[i].first == 'W') continue;

        int neighs{};
        if (i > 0 && ys[i - 1].first == peer(ys[i].first)) ++neighs;
        if (i < sz(ys) - 1 && ys[i + 1].first == peer(ys[i].first)) ++neighs;

        if (!neighs) return false;
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

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
