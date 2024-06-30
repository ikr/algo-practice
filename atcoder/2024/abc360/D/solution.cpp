#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> distinct(vector<ll> xs) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    return xs;
}

vector<ll> milesones(const vector<pll> &AB) {
    vector<ll> result;
    result.reserve(sz(AB) * 2);
    for (const auto &[a, b] : AB) {
        assert(a < b);
        result.push_back(a);
        result.push_back(b + 1);
    }
    return distinct(std::move(result));
}

unordered_map<ll, ll> openings(const vector<pll> &AB) {
    unordered_map<ll, ll> result;
    for (const auto &[a, _] : AB) ++result[a];
    return result;
}

unordered_map<ll, ll> closings(const vector<pll> &AB) {
    unordered_map<ll, ll> result;
    for (const auto &[_, b] : AB) ++result[b + 1];
    return result;
}

constexpr ll num_pairs(const ll n) { return n * (n - 1LL) / 2LL; }

ll num_meeting_pairs(const vector<pll> &AB) {
    const auto ms = milesones(AB);
    const auto os = openings(AB);
    const auto cs = closings(AB);

    ll result{};
    ll currently_open{};

    for (const auto x : ms) {
        if (cs.contains(x)) currently_open -= cs.at(x);
        const auto novel = os.contains(x) ? os.at(x) : 0LL;
        result += num_pairs(novel);
        result += currently_open * novel;
        currently_open += novel;
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    ll T;
    cin >> N >> T;

    string S;
    cin >> S;
    assert(sz(S) == N);

    vector<ll> X(N);
    for (auto &x : X) cin >> x;

    vector<pll> AB(N);
    for (int i = 0; i < N; ++i) {
        if (S[i] == '0') {
            // Negative direction
            AB[i] = {X[i] - T, X[i]};
        } else {
            assert(S[i] == '1'); // Positive direction
            AB[i] = {X[i], X[i] + T};
        }
    }

    cout << num_meeting_pairs(AB) << '\n';
    return 0;
}
