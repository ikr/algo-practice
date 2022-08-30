#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
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

array<int, 3> points(const array<vector<string>, 3> &pws) {
    map<string, int> fs;

    for (const auto &ws : pws) {
        for (const auto &w : ws) {
            ++fs[w];
        }
    }

    // cerr << "fs: " << fs << endl;

    array<int, 3> result{0, 0, 0};

    for (int i = 0; i < sz(pws); ++i) {
        for (const auto &w : pws[i]) {
            if (fs.at(w) == 1) {
                result[i] += 3;
            } else if (fs.at(w) == 2) {
                result[i] += 1;
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        array<vector<string>, 3> pws;
        for (int i = 0; i < sz(pws); ++i) {
            pws[i] = vector<string>(n);
            for (auto &w : pws[i]) cin >> w;
        }

        // cerr << "pws: " << pws << endl;

        cout << points(pws) << '\n';
    }

    return 0;
}
