#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

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

int snap_up_to_closest_counting_arrivals(vi &ds, vi &xs) { return -1; }

int max_arrivals_up(vi ds, vi xs) {
    if (ds.empty() || xs.empty()) return 0;

    drop_unreachable_lower_destinations(ds, xs[0]);
    if (ds.empty()) return 0;

    drop_overrun_upper_boxes(ds.back(), xs);
    if (xs.empty()) return 0;

    return -1;
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
