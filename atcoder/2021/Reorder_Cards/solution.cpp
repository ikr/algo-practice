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

vi firsts(const vector<pii> &ab) {
    vi ans(sz(ab), 0);
    transform(cbegin(ab), cend(ab), begin(ans),
              [](const auto p) { return p.first; });
    return ans;
}

vi seconds(const vector<pii> &ab) {
    vi ans(sz(ab), 0);
    transform(cbegin(ab), cend(ab), begin(ans),
              [](const auto p) { return p.second; });
    return ans;
}

vi distinct_values(vi xs) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    return xs;
}

map<int, int> gather_index(const vi &xs) {
    map<int, int> ans;
    for (int i = 0; i < sz(xs); ++i) {
        ans[xs[i]] = i;
    }
    return ans;
}

vector<pii> compressed_grid(const vector<pii> &ab) {
    const auto rows = distinct_values(firsts(ab));
    const auto idx_ro = gather_index(rows);

    const auto cols = distinct_values(seconds(ab));
    const auto idx_co = gather_index(cols);

    vector<pii> ans(sz(ab));
    transform(cbegin(ab), cend(ab), begin(ans), [&](const pii p) {
        const auto [a, b] = p;
        return pii{idx_ro.at(a), idx_co.at(b)};
    });
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int H, W, N;
    cin >> H >> W >> N;

    vector<pii> ab(N);
    for (auto &[a, b] : ab) {
        cin >> a >> b;
        --a;
        --b;
    }

    for (const auto [ro, co] : compressed_grid(ab)) {
        cout << (ro + 1) << ' ' << (co + 1) << '\n';
    }
    return 0;
}
