#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using iter = vector<ll>::const_iterator;

unordered_map<ll, int> pairwise_sum_counts(const iter first, const iter last) {
    unordered_map<ll, int> ans;

    for (auto it = first; it != prev(last); ++it) {
        for (auto jt = next(it); jt != last; ++jt) {
            ++ans[*it + *jt];
        }
    }

    return ans;
}

void replace_term(unordered_map<ll, int> &ys, const iter first, const iter last,
                  const ll a, const ll b) {
    if (a == b) return;

    for (auto it = first; it != last; ++it) {
        const ll aplus = a + *it;
        --ys[aplus];
        if (!ys[aplus]) ys.erase(aplus);

        ++ys[b + *it];
    }
}

ll first_outlier(const int pre, const vector<ll> &xs) {
    auto ys = pairwise_sum_counts(cbegin(xs), cbegin(xs) + pre);

    for (auto it = cbegin(xs) + pre; it != cend(xs); ++it) {
        if (!ys.count(*it)) return *it;

        const auto jt = it - pre;
        replace_term(ys, jt + 1, it, *jt, *it);
    }

    return -1;
}

pair<iter, iter> summing_up_range(const vector<ll> &xs, const ll target) {
    const int n = xs.size();
    vector<ll> ss(n + 1, 0);
    partial_sum(cbegin(xs), cend(xs), next(begin(ss)));

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const ll s = ss[j + 1] - ss[i];
            if (s == target) return {cbegin(xs) + i, cbegin(xs) + j + 1};
        }
    }

    return {cend(xs), cend(xs)};
}

int main() {
    vector<ll> xs;

    for (string line; getline(cin, line);) {
        xs.push_back(stoll(line));
    }

    const ll outl = first_outlier(25, xs);
    const auto [first, last] = summing_up_range(xs, outl);
    const auto [lo, hi] = minmax_element(first, last);

    cout << (*lo + *hi) << '\n';
    return 0;
}
