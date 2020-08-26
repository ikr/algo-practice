#include <bits/stdc++.h>
using namespace std;

int tree_beauty(const vector<int> &parent, const int step_a, const int step_b,
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

double solve(const vector<int> &parent, const int step_a, const int step_b) {
    const int N = parent.size() - 1;
    int s = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            s += tree_beauty(parent, step_a, step_b, i, j);
        }
    }

    return static_cast<double>(s) / N / N;
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
