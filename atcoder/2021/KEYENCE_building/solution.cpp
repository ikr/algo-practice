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

set<int> possible_area_values() {
    const auto area = [](const int a, const int b) -> int {
        return 4 * a * b + 3 * a + 3 * b;
    };

    set<int> result;
    for (int i = 1; i <= 1000; ++i) {
        for (int j = 1; j <= 1000; ++j) {
            if (area(i, j) > 1000) break;
            result.insert(area(i, j));
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;

    const auto a = possible_area_values();

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;

        if (!a.count(x)) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
