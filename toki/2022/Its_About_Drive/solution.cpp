#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using tri = tuple<ll, ll, ll>;

bool is_possible(const ll N, const ll F, const ll D) {
    map<tri, bool> memo;

    function<bool(ll, ll, ll)> recur;
    recur = [&](const ll n, const ll f, const ll d) -> bool {
        const tri key{n, f, d};

        {
            const auto it = memo.find(key);
            if (it != cend(memo)) return it->second;
        }

        return memo[key] = [&]() -> bool {
            if (f > n || f < 0 || d < 0) return false;
            if (n == 0 && f == 0 && d == 0) return true;
            if (n == 0) return false;

            return recur(n - 1, f - 1, d - f) || recur(n - 1, f, d - f) ||
                   recur(n - 1, f + 1, d - f);
        }();
    };

    return recur(N, F, D);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, F, D;
    cin >> N >> F >> D;

    cout << (is_possible(N, F, D) ? "YES" : "NO") << '\n';
    return 0;
}
