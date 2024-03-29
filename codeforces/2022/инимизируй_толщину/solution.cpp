#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_thickness_of_partitioning(const vector<int> &xs) {
    const auto lo = *min_element(cbegin(xs), cend(xs));

    vector<int> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto range_sum = [&ss](const int a, const int b) -> int {
        return ss[b] - (a ? ss[a - 1] : 0);
    };

    int result = sz(xs);

    for (const int T : ss) {
        if (xs[0] > T) continue;

        int cand = 1;
        int a{};
        int b{};

        for (;;) {
            while (b < sz(xs) - 1 && range_sum(a, b) < T) ++b;

            if (range_sum(a, b) == T) {
                cand = max(cand, b - a + 1);

                if (b < sz(xs) - 1) {
                    a = b + 1;
                    b = a;
                }
            } else {
                break;
            }

            if (b == sz(xs) - 1) {
                cand = max(cand, b - a + 1);
                break;
            }
        }

        if (b == sz(xs) - 1 && range_sum(a, b) == T) {
            result = min(result, cand);
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

        cout << min_thickness_of_partitioning(xs) << '\n';
    }

    return 0;
}
