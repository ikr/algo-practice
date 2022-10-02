#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int max_hits(vector<ll> xs, vector<ll> ys) {
    unordered_map<ll, int> fs;

    for (const auto x : xs) {
        for (const auto y : ys) {
            ++fs[x - y];
        }
    }

    return max_element(
               xbegin(fs), xend(fs),
               [](const auto a, const auto b) { return a.second < b.second; })
        ->second;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<ll> xs(N);
    for (auto &x : xs) cin >> x;

    vector<ll> ys(M);
    for (auto &y : ys) cin >> y;

    cout << max_hits(move(xs), move(ys)) << '\n';
    return 0;
}
