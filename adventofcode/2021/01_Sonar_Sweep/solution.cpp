#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> sliding_triple_sums(const vector<int> &xs) {
    auto curr = accumulate(cbegin(xs), cbegin(xs) + 3, 0);
    vector<int> ans{curr};
    ans.reserve(sz(xs) - 2);

    for (int i = 0; i + 3 < sz(xs); ++i) {
        curr -= xs[i];
        curr += xs[i + 3];
        ans.push_back(curr);
    }

    return ans;
}

int incs_num(vector<int> xs) {
    adjacent_difference(cbegin(xs), cend(xs), begin(xs));
    return inof(count_if(next(cbegin(xs)), cend(xs),
                         [](const int x) { return x > 0; }));
}

int main() {
    vector<int> xs;

    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    cout << incs_num(sliding_triple_sums(xs)) << '\n';
    return 0;
}
