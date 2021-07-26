#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int, int> gather_freqs(const vector<int> &xs) {
    map<int, int> ans;
    for (const int x : xs) {
        ++ans[x];
    }
    return ans;
}

ll max_lids_sum(const vector<int> &xs, const int k) {
    auto fs = gather_freqs(xs);
    int available_boxes = k;

    ll ans = 0;
    while (fs[0] && available_boxes) {
        int lid_max = 0;

        for (auto it = begin(fs); it != end(fs); ++it) {
            auto &[k, v] = *it;
            if (k != lid_max || !v) break;
            ++lid_max;
            --v;
        }

        ans += lid_max;
        --available_boxes;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    cout << max_lids_sum(xs, k) << '\n';
    return 0;
}
