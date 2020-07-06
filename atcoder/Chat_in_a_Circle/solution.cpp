#include <bits/stdc++.h>
using namespace std;
using umi = unordered_map<int, int>;
using vi = vector<int>;
using qi = deque<int>;
using ll = long long;

void dec_tail(umi &counts, qi &distinct_xs) {
    const int x = distinct_xs.back();
    --counts[x];

    if (!counts[x]) {
        counts.erase(x);
        distinct_xs.pop_back();
    }
}

ll max_total_comfort(umi &counts, qi distinct_xs) {
    ll ans = 0;

    int hi = 0;
    while (!distinct_xs.empty()) {
        const int x = distinct_xs.front();
        distinct_xs.pop_front();

        ans += hi;
        ans += x * (counts[x] - 1);

        int holes = counts[x] - 1;
        while (holes && !distinct_xs.empty()) {
            ans += x;
            dec_tail(counts, distinct_xs);
            --holes;
        }

        hi = x;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    umi counts;
    vi xs(sz, 0);
    for (auto &x : xs) {
        cin >> x;
        ++counts[x];
    }

    sort(xs.begin(), xs.end(), greater<int>{});
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    cout << max_total_comfort(counts, qi(xs.cbegin(), xs.cend())) << '\n';

    return 0;
}
