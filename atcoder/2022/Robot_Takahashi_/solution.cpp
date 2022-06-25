#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string S;
    cin >> S;
    assert(sz(S) == N);

    vector<int> W(N);
    for (auto &w : W) cin >> w;

    vector<int> idx(N);
    iota(begin(idx), end(idx), 0);

    sort(begin(idx), end(idx),
         [&W](const int i, const int j) -> bool { return W[i] < W[j]; });

    vector<int> pref(N, 0);
    pref[0] = S[idx[0]] == '1' ? 1 : 0;

    for (int i = 1; i < N; ++i) {
        pref[i] = pref[i - 1] + (S[idx[i]] == '1' ? 1 : 0);
    }

    vector<int> suff(N, 0);
    suff[N - 1] = S[idx[N - 1]] == '0' ? 1 : 0;

    for (int i = N - 2; i >= 0; --i) {
        suff[i] = suff[i + 1] + (S[idx[i]] == '0' ? 1 : 0);
    }

    int result{};
    for (int i = 0; i < N; ++i) {
        if (i && W[idx[i - 1]] == W[idx[i]]) continue;

        const auto a = i ? pref[i - 1] : 0;
        const auto b = suff[i];

        result = max(result, N - a - b);
    }
    result = max(result, N - pref.back());

    cout << result << '\n';
    return 0;
}
