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

ll max_subtotal(const map<int, int> &xs) {
    const auto hi =
        max_element(cbegin(xs), cend(xs), [](const auto a, const auto b) {
            return 1LL * a.first * a.second < 1LL * b.first * b.second;
        });

    return 1LL * hi->first * hi->second;
}

ll max_subtotal(const map<int, int> &fs, const vector<int> &ks) {
    assert(!ks.empty());

    const auto hi =
        *max_element(cbegin(ks), cend(ks), [&fs](const auto ka, const auto kb) {
            return 1LL * ka * fs.at(ka) < 1LL * kb * fs.at(kb);
        });

    return 1LL * hi * fs.at(hi);
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
    const auto SA = accumulate(cbegin(A), cend(A), 0LL, plus<ll>{});
    const auto fs = frequencies(A);

    const auto ksa_ksb = [&]() -> pair<vector<int>, vector<int>> {
        auto xs = keys(fs);
        const auto lim =
            remove_if(begin(xs), end(xs), [M](const auto x) { return x >= M; });
        return pair{vector<int>(begin(xs), lim), vector<int>(lim, end(xs))};
    }();
    const auto &ksa = ksa_ksb.first;
    const auto &ksb = ksa_ksb.second;
    if (ksa.empty()) return SA - max_subtotal(fs);

    const auto ss = [&]() -> vector<ll> {
        vector<ll> result(sz(ksa));

        for (int i = 0; i < sz(result); ++i) {
            result[i] =
                (i ? result[i - 1] : 0LL) + 1LL * fs.at(ksa[i]) * ksa[i];
        }

        return result;
    }();

    const auto is_complete_ring = ksa[0] == 0 && sz(ksa) == M;
    if (is_complete_ring) {
        if (ksb.empty()) return SA - ss.back();
        return SA - max_subtotal(fs, ksb) + ss.back();
    } else {
        const auto cycled = ksa[0] == 0 && ksa.back() == M - 1;
        const auto es = interval_end_indices(ksa);

        const auto range_sum = [&ss](const int a, const int b) -> ll {
            return ss[b] - (a ? ss[a - 1] : 0LL);
        };

        const auto universal_sum_from = [&](const int i0) -> ll {
            auto result = range_sum(i0, es[i0]);
            if (cycled && ksa[es[i0]] == M - 1) {
                result += range_sum(0, es[0]);
            }
            return result;
        };

        map<int, int> idx;
        for (int i = 0; i < sz(ksa); ++i) {
            idx[ksa[i]] = i;
        }

        ll hi{};

        for (int i0 = 0; i0 < sz(ksa); ++i0) {
            hi = max(hi, universal_sum_from(i0));
        }

        for (const auto y : ksb) {
            const auto x0 = (ksb[y] + 1) % M;
            if (idx.count(x0)) {
                hi = max(hi, 1LL * y * fs.at(ksb[y]) +
                                 universal_sum_from(idx.at(x0)));
            }
        }

        return SA - hi;
    }
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
