#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> freqs(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

pair<int, int> target_x_f(const vector<int> &xs) {
    const auto fs = freqs(xs);
    int f_max = 1;
    int result = xs[0];

    for (const auto [x, f] : fs) {
        if (f > f_max) {
            f_max = f;
            result = x;
        }
    }

    return {result, f_max};
}

int min_ops(const vector<int> &xs) {
    const auto [x, f] = target_x_f(xs);

    int result{};
    int f_curr = f;
    int cap = 0;

    while (f_curr < sz(xs)) {
        if (!cap) {
            ++result;
            cap = f_curr;
            continue;
        }

        if (cap >= sz(xs) - f_curr) {
            result += sz(xs) - f_curr;
            f_curr = sz(xs);
            continue;
        }

        ++result;
        const auto d = min(sz(xs) - f_curr, cap);
        cap += d;
        result += d;
        f_curr += d;
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

        cout << min_ops(xs) << '\n';
    }

    return 0;
}
