#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
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
        for (auto &x : xs) {
            cin >> x;
        }
        ranges::sort(xs);

        vector<int> front;
        front.reserve(n / 2);

        vector<int> back;
        back.reserve(n / 2);

        for (int i = 0; i != n; ++i) {
            if (i % 2) {
                front.push_back(xs[i]);
            } else {
                back.push_back(xs[i]);
            }
        }

        int result{min(2, sz(xs))};

        for (int i = 1; i < sz(front); ++i) {
            if (front[i] > front[i - 1]) ++result;
        }

        for (int i = 1; i < sz(back); ++i) {
            if (back[i] > back[i - 1]) ++result;
        }

        ranges::reverse(back);
        cout << result << '\n' << front << ' ' << back << '\n';
    }

    return 0;
}
