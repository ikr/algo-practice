#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vb = vector<bool>;
static const int MAXA = 1e6;

bool no_twins(const vi &xs, const int i) {
    const int sz = xs.size();
    const int l = i > 0 ? xs[i - 1] : -1;
    const int r = i < sz - 1 ? xs[i + 1] : -1;
    return l != xs[i] && r != xs[i];
}

void mark_multiples(vb &taken, const int x) {
    for (int y = x; y <= MAXA; y += x) taken[y] = true;
}

int solve_on_sorted(const vi &xs) {
    if (xs.empty()) return 0;
    const int sz = xs.size();
    if (sz == 1 || xs[0] == 1) return 1;

    vb taken(MAXA + 1, false);
    int ans = 0;

    for (int i = 0; i < sz; ++i) {
        if (!taken[xs[i]] && no_twins(xs, i)) {
            mark_multiples(taken, xs[i]);
            ++ans;
        }
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
