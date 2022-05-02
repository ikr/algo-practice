#include <algorithm>
#include <iostream>
#include <iterator>
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &zs) {
    {
        auto ys = zs;

        for (int i = 0; i < sz(ys); i += 2) {
            if (i < sz(ys) - 1 && ys[i] > ys[i + 1]) {
                swap(ys[i], ys[i + 1]);
            }
        }

        if (is_sorted(cbegin(ys), cend(ys))) return true;
    }

    {
        auto ys = zs;

        for (int i = 1; i < sz(ys); i += 2) {
            if (i < sz(ys) - 1 && ys[i] > ys[i + 1]) {
                swap(ys[i], ys[i + 1]);
            }
        }
        return is_sorted(cbegin(ys), cend(ys));
    }
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

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
