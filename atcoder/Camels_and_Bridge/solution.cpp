#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll min_caravan_length(vector<int> &weights, vector<pair<int, int>> &caps_lens) {
    const int n = weights.size();
    sort(begin(weights), end(weights));

    const int m = caps_lens.size();
    sort(begin(caps_lens), end(caps_lens));

    vector<int> len_maxes(m, caps_lens[0].second);
    for (int i = 1; i < m; ++i) {
        len_maxes[i] = max(len_maxes[i - 1], caps_lens[i].second);
    }

    ll ans = 0;
    for (int c = 0; c < n; ++c) {
        const int total_w =
            accumulate(cbegin(weights), cbegin(weights) + c + 1, 0);
        auto it = lower_bound(cbegin(caps_lens), cend(caps_lens),
                              pair<int, int>{total_w, 0});

        if (it == cend(caps_lens)) {
            auto it = lower_bound(cbegin(caps_lens), cend(caps_lens),
                                  pair<int, int>{weights[c], 0});

            if (it == cend(caps_lens)) return -1;

            const int i = distance(cbegin(caps_lens), it);
            ans += len_maxes[i];
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<int> weights(N, 0);
    for (auto &w : weights) cin >> w;

    vector<pair<int, int>> caps_lens(M, {0, 0});
    for (auto &lc : caps_lens) {
        cin >> lc.second >> lc.first;
    }

    cout << min_caravan_length(weights, caps_lens) << '\n';
    return 0;
}
