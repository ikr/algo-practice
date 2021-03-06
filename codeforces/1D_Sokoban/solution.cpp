#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename UnaryPredicate>
vi filter_out(vi xs, const UnaryPredicate p) {
    xs.erase(remove_if(begin(xs), end(xs), p), cend(xs));
    return xs;
}

vi negate_and_reverse(vi xs) {
    transform(cbegin(xs), cend(xs), begin(xs), negate<int>{});
    reverse(begin(xs), end(xs));
    return xs;
}

pair<vi, vi> left_subproblem(const vi &ds, const vi &xs) {
    const auto is_positive = [](const int x) { return x > 0; };
    return {negate_and_reverse(filter_out(ds, is_positive)),
            negate_and_reverse(filter_out(xs, is_positive))};
}

pair<vi, vi> right_subproblem(const vi &ds, const vi &xs) {
    const auto is_negative = [](const int x) { return x < 0; };
    return {filter_out(ds, is_negative), filter_out(xs, is_negative)};
}

void drop_unreachable_lower_destinations(vi &ds, const int x_min) {
    assert(!ds.empty());
    if (x_min <= ds[0]) return;

    auto it = cbegin(ds);
    while (it != cend(ds) && *it < x_min) ++it;
    ds.erase(cbegin(ds), it);
}

void drop_overrun_upper_boxes(const int d_max, vi &xs) {
    assert(!xs.empty());
    if (xs.back() <= d_max) return;
    while (d_max < xs.back()) xs.pop_back();
}

vector<int> prefix_sums_of_arrivals(const vi &ds, const vi &xs) {
    const int m = ds.size();
    vector<bool> hit(m, false);
    for (int i = 0; i < m; ++i) {
        hit[i] = binary_search(cbegin(xs), cend(xs), ds[i]);
    }

    vector<int> ans(m);
    partial_sum(cbegin(hit), cend(hit), begin(ans));
    return ans;
}

int count_in_span(const vi &xs, const int i, const int sz) {
    const auto hi = cbegin(xs) + i + 1;
    const auto lo = lower_bound(cbegin(xs), hi, xs[i] - sz + 1);
    return distance(lo, hi);
}

int scan_measuring_shifts(const vi &ds, const vi &xs, const vi &ss) {
    const int m = ds.size();
    int ans = ss.back();

    for (int i = 0; i < m; ++i) {
        const int d = ds[i];
        const int initial_hits = ss[i];
        const int tail_size =
            distance(cbegin(xs), upper_bound(cbegin(xs), cend(xs), d));
        const int tail_sweep = count_in_span(ds, i, tail_size);

        ans = max(ans, ss.back() - initial_hits + tail_sweep);
    }

    return ans;
}

int max_arrivals_up(vi ds, vi xs) {
    if (ds.empty() || xs.empty()) return 0;

    drop_unreachable_lower_destinations(ds, xs[0]);
    if (ds.empty()) return 0;

    drop_overrun_upper_boxes(ds.back(), xs);
    if (xs.empty()) return 0;

    const auto ss = prefix_sums_of_arrivals(ds, xs);
    return scan_measuring_shifts(ds, xs, ss);
}

int max_arrivals(const vi &ds_, const vi &xs_) {
    int ans = 0;

    for (const auto [ds, xs] :
         {left_subproblem(ds_, xs_), right_subproblem(ds_, xs_)}) {
        ans += max_arrivals_up(move(ds), move(xs));
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

        vi xs(n);
        for (auto &x : xs) cin >> x;

        vi ds(m);
        for (auto &d : ds) cin >> d;

        cout << max_arrivals(ds, xs) << '\n';
    }

    return 0;
}
