#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Vert = tuple<int, int, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<Vert> adjacent_vertices(const vector<vector<int>> &P,
                               const vector<vector<int>> &R,
                               const vector<vector<int>> &D, const Vert &v) {
    const auto N = sz(P);
    const auto [ro, co, p] = v;

    vector<Vert> result{Vert{ro, co, p + P[ro][co]}};
    if (ro < N - 1 && p >= D[ro][co]) {
        result.push_back(Vert{ro + 1, co, p - D[ro][co]});
    }
    if (co < N - 1 && p >= R[ro][co]) {
        result.push_back(Vert{ro, co + 1, p - R[ro][co]});
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<int>> P(N, vector(N, 0));
    for (auto &row : P) {
        for (auto &p : row) cin >> p;
    }

    vector<vector<int>> R(N, vector(N - 1, 0));
    for (auto &row : R) {
        for (auto &r : row) cin >> r;
    }

    vector<vector<int>> D(N - 1, vector(N, 0));
    for (auto &row : D) {
        for (auto &d : row) cin >> d;
    }

    map<Vert, ll> acts;
    acts.emplace(Vert{0, 0, 0}, 0);

    queue<Vert> q;
    q.emplace(0, 0, 0);

    while (!q.empty()) {
        const auto v = q.front();
        q.pop();

        for (const auto &u : adjacent_vertices(P, R, D, v)) {
            if (acts.contains(u)) continue;
            const auto [ro, co, p] = u;
            if (ro == N - 1 && co == N - 1) {
                cout << acts[v] + 1 << '\n';
                return 0;
            }
            acts[u] = acts[v] + 1;
            q.push(u);
        }
    }

    return 0;
}
