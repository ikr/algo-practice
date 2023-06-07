#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint n_choose_2(const mint n) { return n * (n - 1) * mint{2}.inv(); }

mint num_good_removals(const vector<int> &xs) {

    map<pair<int, int>, mint> memo;

    const auto recur = [&](const auto self, const int ev,
                           const int od) -> mint {
        const auto it = memo.find({ev, od});
        if (it != cend(memo)) return it->second;

        return memo[{ev, od}] = [&]() -> mint {
            if (!ev && !od) return 1;

            if (od % 2) {
                return od * self(self, ev, od - 1);
            } else {
                mint ans{};

                if (od) {
                    assert(od >= 2);
                    ans += n_choose_2(od) * self(self, ev, od - 2);
                }

                if (ev) {
                    ans += ev * self(self, ev - 1, od);
                }

                return ans;
            }
        }();
    };

    const auto od0 =
        inof(count_if(cbegin(xs), cend(xs), [](const int x) { return x % 2; }));
    const auto ev0 = sz(xs) - od0;

    return recur(recur, ev0, od0);
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

        cout << num_good_removals(xs).val() << '\n';
    }

    return 0;
}
