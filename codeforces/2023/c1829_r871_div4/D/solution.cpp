#include <bits/stdc++.h>
using namespace std;

bool is_possible(const int n, const int m) {
    map<int, bool> memo;

    const auto recur = [&](const auto self, const int k) -> bool {
        const auto it = memo.find(k);
        if (it != cend(memo)) return it->second;

        return memo[k] = [&]() -> bool {
            if (k == m) return true;
            if (k % 3 || k < m) return false;
            return self(self, k / 3) || self(self, (k / 3) * 2);
        }();
    };

    return recur(recur, n);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        cout << (is_possible(n, m) ? "YES" : "NO") << '\n';
    }

    return 0;
}
