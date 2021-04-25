#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr ll GIG = 1e9;
static constexpr ll ELV = 1e11;
using Tri = tuple<ll, ll, ll>;
using Quad = tuple<ll, ll, ll, ll>;

vector<Tri> positions() {
    const int total_seconds = 12 * 60 * 60;
    vector<Tri> ans(total_seconds);

    for (int s = 0; s < total_seconds; ++s) {
        ans[s] = Tri{s * GIG, (s * GIG * 12LL) % (432LL * ELV),
                     (s * GIG * 720LL) % (432LL * ELV)};
    }

    return ans;
}

ll distance(const ll t1, const ll t2) {
    const ll a = min(t1, t2);
    const ll b = max(t1, t2);
    return min(a + 432 * ELV - b, b - a);
}

Tri fingerprint(const Tri &ts) {
    const auto [a, b, c] = ts;
    return {distance(a, b), distance(b, c), distance(a, c)};
}

ll fingerprints_distance(const Tri &fp1, const Tri &fp2) {
    const auto [a, b, c] = fp1;
    const auto [x, y, z] = fp2;
    return abs(a - x) + abs(b - y) + abs(c - z);
}

pair<int, ll> closest_seconds_index_with_distance(const vector<Tri> &ps,
                                                  const Tri &ts) {
    int index = -1;
    ll dist = LONG_LONG_MAX;

    for (int i = 0; i < sz(ps); ++i) {
        const auto potential =
            fingerprints_distance(fingerprint(ps[i]), fingerprint(ts));

        if (dist > potential) {
            dist = potential;
            index = i;
        }
    }

    return {index, dist};
}

Quad solve(const vector<Tri> &ps, vll ts) {
    priority_queue<pair<ll, pair<vll, int>>> probes;

    sort(begin(ts), end(ts));
    do {
        const auto [index, dist] =
            closest_seconds_index_with_distance(ps, {ts[0], ts[1], ts[2]});

        probes.emplace(-dist, pair{ts, index});
    } while (next_permutation(begin(ts), end(ts)));

    const auto [_, ts_and_index] = probes.top();
    const auto [ordering, index] = ts_and_index;

    const int total_seconds = index;

    return {total_seconds / (60 * 60), (total_seconds / 60) % 60,
            total_seconds % 60, 0};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    const auto ps = positions();

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        ll t1, t2, t3;
        cin >> t1 >> t2 >> t3;

        const auto [h, m, s, n] = solve(ps, {t1, t2, t3});
        cout << "Case #" << i << ": " << h << ' ' << m << ' ' << s << ' ' << n
             << '\n';
    }

    return 0;
}
