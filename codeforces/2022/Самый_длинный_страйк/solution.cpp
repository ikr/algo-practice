#include <algorithm>
#include <iostream>
#include <optional>
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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> compress(const vector<int> &xs, const int k) {
    vector<int> result;
    int cur = -1;
    int n = 0;

    for (const auto x : xs) {
        if (x != cur) {
            if (cur != -1 && n >= k) {
                result.emplace_back(cur);
            }
            cur = x;
            n = 1;
        } else {
            ++n;
        }
    }

    if (n >= k) result.emplace_back(cur);

    return result;
}

optional<pii> solve(const vector<int> &xs, const int k) {
    const auto ys = compress(xs, k);
    if (ys.empty()) return nullopt;

    int l = ys[0];
    int r = ys[0];
    int i = 0;
    int j = 0;

    while (j + 1 < sz(ys)) {
        ++j;
        if (ys[j] - ys[j - 1] != 1) {
            i = j;
        } else {
            if (ys[j] - ys[i] > r - l) {
                l = ys[i];
                r = ys[j];
            }
        }
    }

    return pii{l, r};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        const auto lr = solve(xs, k);
        if (lr) {
            cout << lr->first << ' ' << lr->second << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
