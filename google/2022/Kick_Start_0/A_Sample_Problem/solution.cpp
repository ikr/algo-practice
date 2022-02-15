#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int solve(const vector<int> &xs, const int M) {
    const auto total = accumulate(cbegin(xs), cend(xs), 0);
    return total % M;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, M;
        cin >> N >> M;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs, M) << '\n';
    }

    return 0;
}
