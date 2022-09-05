#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> sorted_freqs(const vector<int> &xs) {
    map<int, int> fs;
    for (const auto x : xs) ++fs[x];

    vector<int> result(sz(fs));
    transform(cbegin(fs), cend(fs), begin(result),
              [](const auto &kv) { return kv.second; });

    sort(begin(result), end(result));
    return result;
}

bool is_possible(const vector<int> &xs, const int K) {
    if (2 * K < sz(xs)) return false;
    const auto fs = sorted_freqs(xs);
    return fs.back() <= 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K;
        cin >> N >> K;

        vector<int> xs(N);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << (is_possible(xs, K) ? "YES" : "NO")
             << '\n';
    }

    return 0;
}
