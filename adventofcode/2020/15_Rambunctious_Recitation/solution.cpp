#include <bits/stdc++.h>
using namespace std;

map<int, int> gather_last_indices_by_value(const vector<int> &xs) {
    const int n = xs.size();
    map<int, int> ans;

    for (int i = 0; i < n; ++i) {
        ans[xs[i]] = i;
    }

    return ans;
}

int num_2020(vector<int> xs) {
    const int x0 = xs.back();
    xs.pop_back();
    auto idx = gather_last_indices_by_value(xs);
    xs.push_back(x0);
    xs.reserve(2020);

    while (xs.size() != 2020) {
        const int x = xs.back();
        const int xi = xs.size() - 1;

        if (!idx.count(x)) {
            xs.push_back(0);
        } else {
            const int j = idx.at(x);
            xs.push_back(xi - j);
        }

        idx[x] = xi;
    }

    return xs.back();
}

int main() {
    const vector<vector<int>> inputs{{0, 3, 6}, {1, 3, 2},          {2, 1, 3},
                                     {1, 2, 3}, {2, 3, 1},          {3, 2, 1},
                                     {3, 1, 2}, {2, 0, 6, 12, 1, 3}};

    for (const auto &input : inputs) {
        cout << num_2020(input) << '\n';
    }
    return 0;
}
