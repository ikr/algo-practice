#include <iostream>
#include <map>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll min_time(const vector<int> &S, const vector<int> &K) {
    map<int, int> idx;
    for (int i = 0; i < sz(K); ++i) {
        idx[K[i]] = i;
    }

    ll result{};

    for (int cur = idx[S[0]], i = 1; i < sz(S); ++i) {
        result += abs(cur - idx[S[i]]);
        cur = idx[S[i]];
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> S(N);
        for (auto &x : S) cin >> x;

        int M;
        cin >> M;

        vector<int> K(M);
        for (auto &x : K) cin >> x;

        cout << "Case #" << i << ": " << min_time(S, K) << '\n';
    }

    return 0;
}
