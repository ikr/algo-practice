#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_yield(const vector<int> &xs) {
    const auto a = [&]() -> map<int, int> {
        map<int, int> result{{xs[0], 1}};
        int s = xs[0];

        for (int i = 1; i < sz(xs); ++i) {
            s += xs[i];
            result.emplace(s, i + 1);
        }

        return result;
    }();

    const auto b = [&]() -> map<int, int> {
        map<int, int> result{{xs.back(), 1}};
        int s = xs.back();

        for (int i = sz(xs) - 2; i >= 0; --i) {
            s += xs[i];
            result.emplace(s, sz(xs) - i);
        }

        return result;
    }();

    int result{};

    for (const auto [k, v] : a) {
        if (b.count(k)) {
            const auto v_ = b.at(k);
            if (v + v_ <= sz(xs)) {
                result = max(result, v + v_);
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        cout << max_yield(xs) << '\n';
    }

    return 0;
}
