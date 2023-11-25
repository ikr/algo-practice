#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    map<int, unordered_set<int>> idx;
    for (int i = 0; i < N; ++i) idx[A[i]].insert(i);

    set<pii> ii;
    for (const auto &[k, _] : idx) {
        if (empty(ii)) {
            ii.emplace(k, k);
        } else {
            const auto [a, b] = *crbegin(ii);
            if (k == b + 1) {
                ii.erase(prev(cend(ii)));
                ii.emplace(a, k);
            } else {
                ii.emplace(k, k);
            }
        }
    }

    const auto mex = [&]() -> int {
        if (empty(ii)) return 0;
        const auto [a, b] = *cbegin(ii);
        if (a) return 0;
        return b + 1;
    };

    const auto remove_from_interval = [](const pii ab,
                                         const int x) -> vector<pii> {
        const auto [a, b] = ab;
        assert(a <= x && x <= b);

        if (a == b) return {};
        if (x == a) return {{a + 1, b}};
        if (x == b) return {{a, b - 1}};
        return {{a, x - 1}, {x + 1, b}};
    };

    const auto add_to_interval = [](const pii ab, const int x) -> pii {
        const auto [a, b] = ab;
        if (x + 1 == a) return {x, b};
        assert(b + 1 == x);
        return {a, x};
    };

    const auto remove_from_intervals = [&](const int x) -> void {
        auto it = ii.lower_bound({x, x});
        if (it == cend(ii)) {
            --it;
        } else {
            const auto [a, b] = *it;
            if (x < a || b < x) --it;
        }

        const auto ab = *it;
        ii.erase(it);
        for (const auto &cd : remove_from_interval(ab, x)) ii.insert(cd);
    };

    const auto add_to_intervals = [&](const int x) -> void {
        auto it = ii.lower_bound({x, x});
        if (it == cend(ii)) --it;
        const auto jt = it == cbegin(ii) ? it : prev(it);

        const auto [a, b] = *it;
        const auto [c, d] = *jt;
        if (x + 1 == a || b + 1 == x) {
            ii.erase({a, b});
            ii.insert(add_to_interval({a, b}, x));
        } else if (x + 1 == c || d + 1 == x) {
            ii.erase({c, d});
            ii.insert(add_to_interval({c, d}, x));
        } else {
            ii.insert({x, x});
        }
    };

    const auto change = [&](const int index, const int new_value) -> void {
        const auto old_value = A[index];

        idx[old_value].erase(index);
        if (empty(idx[old_value])) {
            idx.erase(old_value);
            remove_from_intervals(old_value);
        }

        if (idx.contains(new_value)) {
            idx[new_value].insert(index);
        } else {
            idx[new_value] = {index};
            add_to_intervals(new_value);
        }

        A[index] = new_value;
    };

    for (int k = 1; k <= Q; ++k) {
        int ik, xk;
        cin >> ik >> xk;
        --ik;
        change(ik, xk);
        cout << mex() << '\n';
    }

    return 0;
}
