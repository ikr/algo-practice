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

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int max_total_value_when_boxes_range_removed(const vector<pii> &bags,
                                             const vi &boxes, const int l,
                                             const int r) {
    vi remaining_boxes;
    for (int i = 0; i < l; ++i) remaining_boxes.push_back(boxes[i]);
    for (int i = r + 1; i < sz(boxes); ++i) remaining_boxes.push_back(boxes[i]);
    sort(begin(remaining_boxes), end(remaining_boxes));

    vi bags_by_v(sz(bags));
    iota(begin(bags_by_v), end(bags_by_v), 0);
    sort(begin(bags_by_v), end(bags_by_v), [&](const int lhs, const int rhs) {
        return bags[lhs].second > bags[rhs].second;
    });

    int ans = 0;

    for (const int i : bags_by_v) {
        if (remaining_boxes.empty()) break;
        const auto it = lower_bound(cbegin(remaining_boxes),
                                    cend(remaining_boxes), bags[i].first);
        if (it == cend(remaining_boxes)) continue;

        ans += bags[i].second;
        remaining_boxes.erase(it);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(9) << fixed;

    int n, m, q;
    cin >> n >> m >> q;

    vector<pii> bags(n);
    for (auto &[w, v] : bags) cin >> w >> v;

    vi boxes(m);
    for (auto &box : boxes) cin >> box;

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        cout << max_total_value_when_boxes_range_removed(bags, boxes, l, r)
             << '\n';
    }

    return 0;
}
