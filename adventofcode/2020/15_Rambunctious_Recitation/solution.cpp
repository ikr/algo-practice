#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> gather_last_indices_by_value(const vector<int> &xs) {
    const int n = xs.size();
    unordered_map<int, int> ans;

    for (int i = 0; i < n; ++i) {
        ans[xs[i]] = i;
    }

    return ans;
}

int num_30000000(vector<int> xs) {
    int last_one = xs.back();
    int total = xs.size();
    xs.pop_back();
    auto idx = gather_last_indices_by_value(xs);

    while (total != 30000000) {
        const int x = last_one;
        const int xi = total - 1;

        if (!idx.count(x)) {
            last_one = 0;
        } else {
            const int j = idx.at(x);
            last_one = xi - j;
        }

        idx[x] = xi;
        ++total;
    }

    return last_one;
}

int main() {
    cout << num_30000000({2, 0, 6, 12, 1, 3}) << '\n';

    const vector<vector<int>> inputs{{0, 3, 6}, {1, 3, 2},          {2, 1, 3},
                                     {1, 2, 3}, {2, 3, 1},          {3, 2, 1},
                                     {3, 1, 2}, {2, 0, 6, 12, 1, 3}};

    for (const auto &input : inputs) {
        cout << num_30000000(input) << '\n';
    }
    return 0;
}
