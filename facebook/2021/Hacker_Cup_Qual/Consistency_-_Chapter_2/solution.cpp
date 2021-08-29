#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;
static constexpr int INF = 1e9;

vi numerize(const string &xs) {
    vi ans(sz(xs), -1);
    transform(cbegin(xs), cend(xs), begin(ans),
              [](const char c) { return inof(c) - inof('A'); });
    return ans;
}

int min_ops_to_consistency(const vi &src, const vvi &g) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string xs;
        cin >> xs;

        int k;
        cin >> k;

        vvi g(AZ);
        for (int i = 0; i < k; ++i) {
            string ab;
            cin >> ab;

            const auto uv = numerize(ab);
            g[uv[0]].push_back(uv[1]);
        }

        cout << "Case #" << i << ": " << min_ops_to_consistency(numerize(xs), g)
             << '\n';
    }

    return 0;
}
