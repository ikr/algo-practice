#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> frequencies(const vector<int> &xs) {
    map<int, int> result;
    for (const auto x : xs) ++result[x];
    return result;
}

vector<int> keys(const map<int, int> &xs) {
    vector<int> result(sz(xs));
    transform(cbegin(xs), cend(xs), begin(result),
              [](const auto kv) { return kv.first; });
    return result;
}

vector<int> interval_end_indices(const vector<int> &xs) {
    const auto n = sz(xs);
    vector<int> result(n);
    result.back() = n - 1;

    for (int i = n - 2; i >= 0; --i) {
        if (xs[i] + 1 == xs[i + 1]) {
            result[i] = result[i + 1];
        } else {
            result[i] = i;
        }
    }

    return result;
}

ll min_remaining_sum(const vector<int> &A, const int M) {
    const auto fs = frequencies(A);
    const auto ks = keys(fs);
    const auto es = interval_end_indices(A);

    const auto ss = [&]() -> vector<ll> {
        assert(!ks.empty());
        vector<ll> result(sz(ks));

        for (int i = 0; i < sz(result); ++i) {
            result[i] = (i ? result[i - 1] : 0LL) + 1LL * fs.at(ks[i]) * ks[i];
        }

        return result;
    }();

    const auto range_sum = [&](const int a, const int b) -> ll {
        return ss[b] - (a ? ss[a - 1] : 0LL);
    };

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << min_remaining_sum(A, M) << '\n';
    return 0;
}
