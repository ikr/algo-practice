#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_happy(const vector<int> &xs) {
    const auto N = sz(xs);
    deque<int> idx(N, 0);
    iota(begin(idx), end(idx), 0);

    int result{};
    int shift = 0;

    do {
        int cur{};
        for (int i = 0; i < N; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (idx[(i + j + N) % N] == xs[i]) {
                    ++cur;
                    break;
                }
            }
        }

        result = max(result, cur);

        const auto x = idx.back();
        idx.pop_back();
        idx.push_front(x);
        ++shift;
    } while (shift <= N);

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << max_happy(xs) << '\n';
    return 0;
}
