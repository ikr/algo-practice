#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int tree_beauty(const vi &parent, const int step_a, const int step_b,
                const int start_a, const int start_b) {
    const auto step_up = [&parent](int x, int step) -> int {
        while (x > 0 && step > 0) {
            x = parent[x];
            --step;
        }

        return x;
    };

    unordered_set<int> colored;

    const auto color_up = [&parent, &colored, &step_up](const int start,
                                                        const int step) {
        int x = start;

        do {
            colored.insert(x);
            x = step_up(x, step);
        } while (x > 0);
    };

    color_up(start_a, step_a);
    color_up(start_b, step_b);

    return colored.size();
}

vi gather_leaves(const vi &parent) {
    const int N = parent.size() - 1;
    const unordered_set<int> p_set(cbegin(parent), cend(parent));

    vi ans;
    ans.reserve(N / 2);
    for (int i = 1; i <= N; ++i) {
        if (!p_set.count(i)) ans.push_back(i);
    }
    return ans;
}

vi gather_skip_descendants_counts(const vi &parent, const vi &leaves,
                                  const int step) {
    const int N = parent.size() - 1;
    vi ans(N + 1, 0);

    for (const int l : leaves) {
        int curr = l;
        vi chain;
        do {
            chain.push_back(0);
            const int chain_size = chain.size();

            if (chain_size - 1 - step >= 0) {
                int &me = chain.back();
                me = chain[chain_size - 1 - step] + 1;
                ans[curr] += me;
            }

            curr = parent[curr];
        } while (curr);
    }

    return ans;
}

double solve(const vi &parent, const int step_a, const int step_b) {
    const int N = parent.size() - 1;
    const auto leaves = gather_leaves(parent);
    cout << gather_skip_descendants_counts(parent, leaves, 1) << '\n';
    return leaves.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(6) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, A, B;
        cin >> N >> A >> B;

        vi parent(N + 1, 0);
        for (int i = 2; i <= N; ++i) cin >> parent[i];

        cout << "Case #" << i << ": " << solve(parent, A, B) << '\n';
    }

    return 0;
}
