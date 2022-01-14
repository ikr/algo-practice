#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<bool> trained(m, false);
    int ans{};

    for (int i = 0; i < n; ++i) {
        char kind;
        cin >> kind;
        assert(kind == '-' || kind == '+');

        string xs(m, ' ');
        cin >> xs;
        assert(sz(xs) == m);

        bool unhappy = false;
        for (int j = 0; j < m; ++j) {
            const auto yes = xs[j] == '1';

            if (kind == '+') { // self
                trained[j] = trained[j] || yes;
            } else { // instructed
                if (!yes) continue;
                if (!trained[j]) {
                    unhappy = true;
                }
                trained[j] = false;
            }
        }
        if (unhappy) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
