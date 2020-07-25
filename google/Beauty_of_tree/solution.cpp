#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

unordered_multimap<int, int> gather_children(const vector<int> &parent) {
    const int N = parent.size() - 1;
    unordered_multimap<int, int> ans;
    for (int i = 2; i <= N; ++i) {
        ans.emplace(parent[i], i);
    }
    return ans;
}

vector<int>
gather_counts_by_level(const int N,
                       const unordered_multimap<int, int> &children) {
    vector<int> ans(N, 0);
    ans[0] = 1;

    function<void(int, int)> recur;
    recur = [&ans, &children, &recur](const int level, const int node) {
        const auto fl = children.equal_range(node);
        for (auto it = fl.first; it != fl.second; ++it) {
            ++ans[level + 1];
            recur(level + 1, it->second);
        }
    };

    recur(0, 1);
    return ans;
}

double solve(const vector<int> &parent, const int A, const int B) {
    const auto counts_by_level =
        gather_counts_by_level(parent.size() - 1, gather_children(parent));

    cout << counts_by_level << '\n';

    return -1.009;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(13);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, A, B;
        cin >> N >> A >> B;

        vector<int> parent(N + 1, 0);
        for (int i = 2; i <= N; ++i) cin >> parent[i];

        cout << "Case #" << i << ": " << solve(parent, A, B) << '\n';
    }

    return 0;
}
