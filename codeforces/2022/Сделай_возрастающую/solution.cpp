#include <algorithm>
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

using pii = pair<int, int>;

pii ops_to_be_smaller_than(const int b, int x) {
    if (b == 0) return {-1, x};

    int result{};

    while (x >= b) {
        x /= 2;
        ++result;
    }

    return {result, x};
}

int min_ops(vector<int> xs) {
    int result{};

    for (int i = sz(xs) - 2; i >= 0; --i) {
        // cerr << xs << endl;
        const auto [o, y] = ops_to_be_smaller_than(xs[i + 1], xs[i]);
        if (o == -1) return -1;
        xs[i] = y;
        result += o;
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << min_ops(move(xs)) << '\n';
    }

    return 0;
}
