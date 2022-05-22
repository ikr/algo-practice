#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <vector>
using namespace std;
using ll = long long;
using vi = vector<int>;

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

optional<vi> alans_subset(const int N, const ll X, const ll Y) {
    assert(N <= 15);
    vi xs(N);
    iota(begin(xs), end(xs), 1);
    const int total = (N * (N + 1)) / 2;

    for (int bits = 1; bits < (1 << N) - 1; ++bits) {
        int s1{};

        for (int i = 0; i < N; ++i) {
            if (bits & (1 << i)) {
                s1 += i + 1;
            }
        }

        const auto s2 = total - s1;

        if (Y * s1 == X * s2) {
            vi ans;
            for (int i = 0; i < N; ++i) {
                if (bits & (1 << i)) ans.push_back(i + 1);
            }
            return ans;
        }
    }

    return nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, X, Y;
        cin >> N >> X >> Y;

        const auto ans = alans_subset(N, X, Y);
        cout << "Case #" << i << ": " << (ans ? "POSSIBLE" : "IMPOSSIBLE")
             << '\n';
        if (ans) cout << sz(*ans) << '\n' << *ans << '\n';
    }

    return 0;
}
