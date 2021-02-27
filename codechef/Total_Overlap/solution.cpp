#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

enum class End { LEFT, RIGHT };

set<pii>::iterator add_interval(set<pii> &is, int l, int r) {
    if (l == r) return is.end();
    auto it = is.lower_bound({l, r}), before = it;

    while (it != is.end() && it->first <= r) {
        r = max(r, it->second);
        before = it = is.erase(it);
    }

    if (it != is.begin() && (--it)->second >= l) {
        l = min(l, it->first);
        r = max(r, it->second);
        is.erase(it);
    }

    return is.insert(before, {l, r});
}

vector<pair<int, End>> gather_endpoints(const set<pii> &xs) {
    const int n = xs.size();
    vector<pair<int, End>> ans(2 * n);

    for (auto [xit, ait] = pair{cbegin(xs), begin(ans)}; xit != cend(xs);
         ++xit) {
        *ait = {xit->first, End::LEFT};
        ++ait;

        *ait = {xit->second, End::RIGHT};
        ++ait;
    }

    return ans;
}

constexpr bool intersect(const pii ab, const pii cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    return !(b < c || d < a);
}

int intersection_length(const pii ab, const pii cd) {
    array<int, 4> xs{ab.first, ab.second, cd.first, cd.second};
    sort(begin(xs), end(xs));
    return xs[2] - xs[1];
}

int total_overlap(set<pii> xs, set<pii> ys) {
    const auto yses = gather_endpoints(ys);
    int ans = 0;
    auto it = cbegin(yses);

    for (const auto [a, b] : xs) {
        it = lower_bound(it, cend(yses), pair{a, End::LEFT});
        if (it == cend(yses)) break;
        if (it->second == End::RIGHT) --it;

        do {
            ans += intersection_length({it->first, next(it)->first}, {a, b});
            it += 2;
        } while (it != cend(yses) &&
                 intersect({it->first, next(it)->first}, {a, b}));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        set<pii> xs;
        for (int i = 0; i < n; ++i) {
            int l, r;
            cin >> l >> r;
            add_interval(xs, l, r);
        }

        set<pii> ys;
        for (int i = 0; i < m; ++i) {
            int l, r;
            cin >> l >> r;
            add_interval(ys, l, r);
        }

        cout << total_overlap(move(xs), move(ys)) << '\n';
    }

    return 0;
}
