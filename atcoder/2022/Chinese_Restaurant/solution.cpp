#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_happy(const vector<int> &xs) {
    const auto N = sz(xs);
    const auto mod_norm = [N](const int x) -> int { return ((x % N) + N) % N; };
    vector matches_by_notches(N, 0);

    for (int i = 0; i < N; ++i) {
        for (const auto j : {xs[i] - (i - 1), xs[i] - i, xs[i] - (i + 1)}) {
            ++matches_by_notches[mod_norm(j)];
        }
    }

    return *max_element(cbegin(matches_by_notches), cend(matches_by_notches));
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
