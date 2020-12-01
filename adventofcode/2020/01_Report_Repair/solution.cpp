#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;

unordered_multimap<int, pi>
gather_indices_by_values_sum(const vector<int> &xs) {
    const int n = xs.size();
    unordered_multimap<int, pi> ans;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ans.emplace(xs[i] + xs[j], pi{i, j});
        }
    }

    return ans;
}

ll product_of_triple_summing_up_to_2020(const vector<int> &xs) {
    const auto indices_by_values_sum = gather_indices_by_values_sum(xs);
    const int n = xs.size();

    for (int i = 0; i < n; ++i) {
        const auto [first, last] =
            indices_by_values_sum.equal_range(2020 - xs[i]);

        for (auto it = first; it != last; ++it) {
            const auto [j, k] = it->second;
            if (i == j || i == k) continue;

            return static_cast<ll>(xs[i]) * xs[j] * xs[k];
        }
    }

    assert(false && "/o\\");
    return -1;
}

int main() {
    vector<int> xs;

    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    cout << product_of_triple_summing_up_to_2020(xs) << '\n';
    return 0;
}
