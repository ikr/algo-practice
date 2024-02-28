#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pli = pair<ll, int>;

static constexpr ll Inf = 3'000'000'000LL * 1'000'000'000LL;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

struct Schedule final {
    ll l;
    ll d;
    ll k;
    ll c;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g_(N);
    map<pii, Schedule> timetable;

    for (int i = 1; i <= M; ++i) {
        Schedule sch;
        cin >> sch.l >> sch.d >> sch.k >> sch.c;

        int a, b;
        cin >> a >> b;
        --a;
        --b;

        timetable.emplace(pii{a, b}, sch);
        g_[b].push_back(a);
    }

    vector<ll> F(N, -Inf);
    set<pli> pq;
    pq.emplace(Inf, N - 1);

    while (!pq.empty()) {
        auto [f, u] = *cbegin(pq);
        f = -f;
        pq.erase(cbegin(pq));

        for (const auto v : g_[u]) {
            const auto it = timetable.find(pii{v, u});
            assert(it != cend(timetable));
            const auto [l, d, k, c] = it->second;

            if (f == -Inf) {
                pq.erase(pli{-F[v], v});
                F[v] = l + (k - 1) * d;
                pq.emplace(-F[v], v);
            } else if (l + c <= f) {
                const auto j = min((f - l - c) / d, k - 1);
                assert(0LL <= j && j < k);
                const auto fv = l + j * d;
                if (fv > F[v]) {
                    pq.erase(pli{-F[v], v});
                    F[v] = fv;
                    pq.emplace(-fv, v);
                }
            }
        }
    }

    F.pop_back();
    for (const auto f : F) {
        if (f > -Inf) {
            cout << f << '\n';
        } else {
            cout << "Unreachable\n";
        }
    }

    return 0;
}
