#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

template <typename UnaryPredicate>
vi filter_out(vi xs, const UnaryPredicate p) {
    xs.erase(remove_if(begin(xs), end(xs), p), cend(xs));
    return xs;
}

vi negate_all(vi xs) {
    transform(cbegin(xs), cend(xs), begin(xs), negate<int>{});
    return xs;
}

pair<vi, vi> left_subproblem(const vi &ds, const vi &xs) {
    const auto is_positive = [](const int x) { return x > 0; };
    return {negate_all(filter_out(ds, is_positive)),
            negate_all(filter_out(xs, is_positive))};
}

pair<vi, vi> right_subproblem(const vi &ds, const vi &xs) {
    const auto is_negative = [](const int x) { return x < 0; };
    return {filter_out(ds, is_negative), filter_out(xs, is_negative)};
}

int max_arrivals_up(vi ds, vi xs) {
    sort(begin(ds), end(ds));
    sort(begin(xs), end(xs));
    return 0;
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
