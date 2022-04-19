#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_cost(const ll a, const ll b, const vector<int> &xs) {
    int icap = 0;
    int iedg = 0;
    ll result{};

    while (iedg != sz(xs) - 1) {
        // cerr << "UP icap:" << icap << " iedg:" << iedg << endl;

        if (icap == iedg) {
            result += b * (xs[icap + 1] - xs[icap]);
            ++iedg;
            // cerr << "take" << endl;
        } else {
            assert(iedg > icap);
            const auto re = sz(xs) - iedg - 1;
            const auto cost_from = [&](const int j) -> ll {
                return a * (xs[j] - xs[icap]) + b * (xs.back() - xs[iedg + 1]) +
                       b * re * (xs[iedg + 1] - xs[j]);
            };

            if (cost_from(icap + 1) <= cost_from(icap)) {
                result += a * (xs[icap + 1] - xs[icap]);
                ++icap;
                // cerr << "move" << endl;
            } else {
                result += b * (xs[iedg + 1] - xs[icap]);
                ++iedg;
                // cerr << "take" << endl;
            }
        }

        // cerr << "DN icap:" << icap << " iedg:" << iedg << " result:" <<
        // result
        //      << endl;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;

        vector<int> xs{0};
        xs.reserve(n + 1);

        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            xs.push_back(x);
        }

        cout << min_cost(a, b, xs) << '\n';
    }

    return 0;
}
