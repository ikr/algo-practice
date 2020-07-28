#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

ll max_a_score(const vll &xs) {
    const int sz = xs.size();
    
    vll psums(sz, 0);
    partial_sum(xs.cbegin(), xs.cend(), psums.begin());
    const auto range_sum = [&psums](const int l, const int r) {
        const ll b = psums[r];
        const ll a = l > 0 ? psums[l - 1] : 0;
        return b - a;
    };
    
    // score when playing [from index l] [to index r]
    vvll score(sz, vll(sz, 0));
    
    for (int r = 0; r != sz; ++r) {
        score[r][r] = xs[r];
        
        for (int l = r - 1; l >= 0; --l) {
            score[l][r] = range_sum(l, r) - min(score[l + 1][r], score[l][r - 1]);
        }
    }
    
    return score.front().back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vll xs(sz, 0);
    for (auto &x : xs) cin >> x;
    cout << max_a_score(xs) << '\n';
    return 0;
}
