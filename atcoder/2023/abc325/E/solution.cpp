#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll Inf = 1'000'000'000LL * 1'000'000'000LL;

vector<ll> distances_by_car_from_0(const vector<vector<ll>> &D, const ll A) {
    const int N = sz(D);
    vector<ll> ans(N, Inf);
    ans[0] = 0;
    vector<bool> u(N, false);

    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (!u[j] && (v == -1 || ans[j] < ans[v])) v = j;
        }
        if (ans[v] == Inf) break;

        u[v] = true;
        for (int to = 0; to < N; ++to) {
            const auto len = D[v][to] * A;
            if (ans[v] + len < ans[to]) ans[to] = ans[v] + len;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    ll A, B, C;
    cin >> A >> B >> C;

    vector<vector<ll>> D(N, vector(N, Inf));
    for (auto &row : D) {
        for (auto &x : row) cin >> x;
    }

    const auto D1 = distances_by_car_from_0(D, A);

    vector<ll> D2(N, Inf);
    for (int v = 0; v < N; ++v) {
        D2[v] = D[v][N - 1] * B + C;
    }
    vector<bool> u(N, false);

    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (!u[j] && (v == -1 || D2[j] < D2[v])) v = j;
        }

        if (D2[v] == Inf) break;

        u[v] = true;
        for (int from = 0; from < N; ++from) {
            const auto len = D[from][v] * B + C;
            if (len + D2[from] < D2[v]) D2[v] = D2[from] + len;
        }
    }

    ll result = Inf;
    for (int v = 0; v < N; ++v) {
        result = min(result, D1[v] + D2[v]);
    }
    cout << result << '\n';
    return 0;
}
