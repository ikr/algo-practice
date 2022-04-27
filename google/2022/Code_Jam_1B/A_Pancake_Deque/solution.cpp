#include <algorithm>
#include <cassert>
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

int solve(const vector<int> &xs) {
    vector<int> tl;
    int i = 0, j = sz(xs) - 1;

    const auto accommodate = [&](const int x) {
        if (tl.empty()) {
            tl.push_back(x);
            return;
        }

        if (tl[0] > x) {
            tl[0] = x;
            return;
        }

        const auto it = lower_bound(begin(tl), end(tl), x);

        if (it == end(tl)) {
            tl.push_back(x);
            return;
        }

        if (*it == x) {
            const auto jt = upper_bound(it, end(tl), x);

            if (jt == end(tl)) {
                tl.push_back(x);
            } else {
                *jt = x;
            }

            return;
        }

        assert(it != begin(tl));
        *it = x;
    };

    while (i <= j) {
        if (xs[i] <= xs[j]) {
            accommodate(xs[i]);
            cerr << "acc " << i << " tl: " << tl << endl;
            ++i;
        } else {
            accommodate(xs[j]);
            cerr << "acc " << j << " tl: " << tl << endl;
            --j;
        }
    }

    return sz(tl);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
