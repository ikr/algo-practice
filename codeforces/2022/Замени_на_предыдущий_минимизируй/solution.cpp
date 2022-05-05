#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

string best_shot(string xs, int k) {
    if (k >= AZ - 1) return string(sz(xs), 'a');
    vector<int> decs(AZ, 0);

    for (auto &x : xs) {
        x = chof(inof(x) - decs[inof(x) - inof('a')]);

        const auto hi = inof(x) - inof('a');
        const auto d = min(k, hi);

        for (int i = 0; i < d; ++i) {
            const auto d_ = d - i;
            decs[inof(x) - inof('a') - i] += d_;
        }

        x = chof(inof(x) - d);
        k -= d;
    }

    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << best_shot(move(xs), k) << '\n';
    }

    return 0;
}
