#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
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

bool is_symm(const vector<int> &xs) {
    auto ys = xs;
    ranges::reverse(ys);

    vector<int> buf;
    int i{};
    int baseline{};
    while (i < ssize(ys)) {
        auto y = ys[i];
        while (y > baseline) {
            buf.push_back(ssize(ys) - i);
            // cerr << "buf: " << buf << endl;
            --y;
            if (size(buf) > size(xs)) return false;
        }
        baseline = ys[i];

        i = inof(ranges::upper_bound(ys, baseline) - ranges::cbegin(ys));
    }

    return buf == xs;
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

        cout << (is_symm(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
