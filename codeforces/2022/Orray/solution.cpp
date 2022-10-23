#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int mlog2(const int x) {
    return 8U * sizeof(int) - __builtin_clz(x) - 1;
}

int snap_the_mask(const int x) {
    int result{};

    for (auto i = mlog2(x); i >= 0; --i) {
        if ((x & (1 << i)) == 0) {
            result |= (1 << i);
        }
    }

    return result;
}

vector<int> optimal_order(vector<int> xs) {
    vector<int> result;
    auto mask = ~0;

    for (; !xs.empty();) {
        const auto it =
            max_element(cbegin(xs), cend(xs), [mask](const int a, const int b) {
                return (a & mask) < (b & mask);
            });

        const auto x = *it;
        const auto mask_ = snap_the_mask(x) | (mask == ~0 ? 0 : mask);
        xs.erase(it);
        result.push_back(x);

        if (mask_ == mask) break;
        mask = mask_;
    }

    result.insert(cend(result), cbegin(xs), cend(xs));
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

        cout << optimal_order(move(xs)) << '\n';
    }

    return 0;
}
