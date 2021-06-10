#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, set<int>> steps_by_num(const int x) {
    map<int, set<int>> ans;

    function<void(int, int)> recur;
    recur = [&](const int steps, const int y) {
        for (int i = 2; llof(i) * i <= llof(y); ++i) {
            if (y % i) continue;
            const int q = y / i;
            ans[i].insert(steps + 1);
            ans[q].insert(steps + 1);

            recur(steps + 1, i);
            recur(steps + 1, q);
        }
    };

    recur(0, x);
    return ans;
};

bool is_possible(const int a, const int b, const int k) {
    const auto sbn_a = steps_by_num(a);
    const auto sbn_b = steps_by_num(b);

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int a, b, k;
        cin >> a >> b >> k;
        cout << (is_possible(a, b, k) ? "YES\n" : "NO\n");
    }

    return 0;
}
