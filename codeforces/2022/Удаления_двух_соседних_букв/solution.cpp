#include <iostream>
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

vector<int> indices_of(const string &xs, const char y) {
    vector<int> result;
    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == y) result.push_back(i);
    }
    return result;
}

bool is_possible(const string &xs, const char r) {
    for (const auto i : indices_of(xs, r)) {
        const auto pre = i;
        const auto post = sz(xs) - i - 1;
        if (pre % 2 == 0 && post % 2 == 0) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        char r;
        cin >> r;

        cout << (is_possible(xs, r) ? "YES" : "NO") << '\n';
    }

    return 0;
}
