#include <bits/stdc++.h>
using namespace std;

struct Ori final {
    pair<int, int> dim;
    int index;
};

using Iter = vector<Ori>::const_iterator;

void sort_by_a(vector<Ori> &oris) {
    sort(begin(oris), end(oris), [&](const auto lhs, const auto rhs) {
        return lhs.dim.first > rhs.dim.first;
    });
}

vector<int> gather_suff_min_b_indices(const vector<Ori> &oris) {
    const int n = oris.size();
    vector<int> ans(n, n - 1);

    for (int i = n - 2; i >= 0; --i) {
        ans[i] =
            oris[ans[i + 1]].dim.second <= oris[i].dim.second ? ans[i + 1] : i;
    }

    return ans;
}

template <typename T> constexpr pair<T, T> flip_pair(const pair<T, T> &ab) {
    return {ab.second, ab.first};
}

vector<Ori> gather_orientations_sorted_by_a(const vector<pair<int, int>> &ab) {
    const int n = ab.size();
    vector<Ori> ans(2 * n);

    for (int i = 0; i < n; ++i) {
        ans[i * 2] = {ab[i], i};
        ans[i * 2 + 1] = {flip_pair(ab[i]), i};
    }

    sort_by_a(ans);
    return ans;
}

int suggest_in_front(const Iter first, const Iter last, const Iter it,
                     const vector<int> &suff_min_b) {
    if (it->dim.first == prev(last)->dim.first) return -1;

    const auto lo = partition_point(it, last, [&](const Ori &ori) {
        return ori.dim.first == it->dim.first;
    });

    if (lo == last) return -1;

    const int j = distance(first, lo);
    const auto lolo = *(first + suff_min_b[j]);
    if (lolo.dim.second >= it->dim.second) return -1;
    return lolo.index;
}

vector<int> in_fronts(const vector<pair<int, int>> &ab) {
    const auto oris = gather_orientations_sorted_by_a(ab);
    const auto suff_min_b = gather_suff_min_b_indices(oris);

    vector<int> ans(ab.size(), -1);

    for (auto it = cbegin(oris); it != cend(oris); ++it) {
        if (ans[it->index] >= 0) continue;

        ans[it->index] =
            suggest_in_front(cbegin(oris), cend(oris), it, suff_min_b);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> ab(n);
        for (auto &[a, b] : ab) cin >> a >> b;

        const auto ans = in_fronts(ab);
        for (auto it = cbegin(ans); it != cend(ans); ++it) {
            if (it != ans.cbegin()) cout << ' ';
            cout << (*it == -1 ? -1 : (*it + 1));
        }
        cout << '\n';
    }

    return 0;
}
