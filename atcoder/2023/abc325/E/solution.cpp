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

ll distance_by_train_to_N_minus_1(const vector<vector<ll>> &D, const ll B,
                                  const ll C, const int s) {
    const int N = sz(D);
    vector<ll> ans(N, Inf);
    ans[s] = 0;

    set<pair<ll, int>> q;
    q.emplace(0, s);

    while (!empty(q)) {
        const auto v = cbegin(q)->second;
        q.erase(cbegin(q));

        for (int to = 0; to < N; ++to) {
            const auto len = D[v][to] * B + C;
            if (ans[v] + len < ans[to]) {
                q.erase({ans[to], to});
                ans[to] = ans[v] + len;
                q.emplace(ans[to], to);
            }
        }
    }

    return ans.back();
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

    ll result = Inf;
    const auto d1 = distances_by_car_from_0(D, A);
    for (int i = 0; i < N; ++i) {
        result =
            min(result, d1[i] + distance_by_train_to_N_minus_1(D, B, C, i));
    }

    cout << result << '\n';
    return 0;
}
