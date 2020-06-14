#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vb = vector<bool>;

bool no_twins(const vi &xs, const int i) {
    const int sz = xs.size();
    const int l = i > 0 ? xs[i - 1] : -1;
    const int r = i < sz - 1 ? xs[i + 1] : -1;
    return l != xs[i] && r != xs[i];
}

void mark_multiples(const int max_a, vb &taken, const int x) {
    for (int y = x; y <= max_a; y += x) taken[y] = true;
}

int solve_on_sorted(const vi &xs) {
    if (xs.empty()) return 0;
    const int sz = xs.size();

    vb taken(xs.back() + 1, false);
    int ans = 0;

    for (int i = 0; i < sz; ++i) {
        if (i > 0 && xs[i] == xs[i - 1]) continue;
        if (!taken[xs[i]] && no_twins(xs, i)) ++ans;
        mark_multiples(xs.back(), taken, xs[i]);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz;
    cin >> sz;
    vi xs(sz, 0);
    for (auto &x : xs) cin >> x;
    sort(xs.begin(), xs.end());
    cout << solve_on_sorted(xs) << '\n';

    return 0;
}
