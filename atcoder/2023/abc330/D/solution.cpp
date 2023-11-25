#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> G(N);
    for (auto &row : G) {
        cin >> row;
        assert(sz(row) == N);
    }

    vector<vector<int>> ocs(N);
    vector<vector<int>> ors(N);

    for (int ro = 0; ro < N; ++ro) {
        for (int co = 0; co < N; ++co) {
            if (G[ro][co] != 'o') continue;
            ocs[ro].push_back(co);
            ors[co].push_back(ro);
        }
    }

    ll result{};
    for (int ro = 0; ro < N; ++ro) {
        for (int co = 0; co < N; ++co) {
            if (G[ro][co] != 'o') continue;

            const auto hi_in_ro = sz(ocs[ro]) - 1;
            const auto i_in_ro =
                inof(lower_bound(cbegin(ocs[ro]), cend(ocs[ro]), co) -
                     cbegin(ocs[ro]));

            const auto hi_in_co = sz(ors[co]) - 1;
            const auto i_in_co =
                inof(lower_bound(cbegin(ors[co]), cend(ors[co]), ro) -
                     cbegin(ors[co]));

            result += (hi_in_ro - i_in_ro) * i_in_co;
            result += i_in_ro * i_in_co;
            result += i_in_ro * (hi_in_co - i_in_co);
            result += (hi_in_ro - i_in_ro) * (hi_in_co - i_in_co);
        }
    }
    cout << result << '\n';
    return 0;
}
