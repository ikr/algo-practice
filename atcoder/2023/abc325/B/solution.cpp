#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    map<int, ll> people_by_hour;

    for (int i = 0; i < N; ++i) {
        int w, x;
        cin >> w >> x;

        const auto lo = 9 - x;
        const auto hi = 18 - x;

        for (int j = lo; j < hi; ++j) {
            people_by_hour[(j + 24) % 24] += w;
        }
    }

    ll result{};
    for (const auto &[_, w] : people_by_hour) {
        result = max(result, w);
    }
    cout << result << '\n';
    return 0;
}
