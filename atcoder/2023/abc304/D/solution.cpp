#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int W, H;
    cin >> W >> H;

    int N;
    cin >> N;

    vector<pii> PQ(N);
    for (auto &[p, q] : PQ) cin >> p >> q;

    int sa;
    cin >> sa;

    vector<int> A(sa);
    for (auto &a : A) cin >> a;

    const auto horizontal_frequencies =
        [&](const pii vert_band) -> vector<int> {
        const auto [up, dn] = vert_band;
        vector<int> result(sa + 1, 0);

        for (const auto &[p, q] : PQ) {
            if (dn <= q && q <= up) {
                const auto it = upper_bound(cbegin(A), cend(A), p);
                const auto i = inof(it - cbegin(A));
                ++result[i];
            }
        }

        return result;
    };

    int sb;
    cin >> sb;

    vector<int> B(sb);
    for (auto &b : B) cin >> b;

    vector<int> vert_freq(sb + 1, 0);
    for (const auto &[_, q] : PQ) {
        const auto it = upper_bound(cbegin(B), cend(B), q);
        const auto i = inof(it - cbegin(B));
        ++vert_freq[i];
    }

    const auto [lo, hi] = minmax_element(cbegin(vert_freq), cend(vert_freq));
    const auto ilo = inof(lo - cbegin(vert_freq));
    const auto lo0 = ilo == 0 ? 0 : B[ilo - 1];
    const auto lo1 = ilo == sb ? H : B[ilo];

    const auto ihi = inof(hi - cbegin(vert_freq));
    const auto hi0 = ihi == 0 ? 0 : B[ihi - 1];
    const auto hi1 = ihi == sb ? H : B[ihi];

    const auto m = [&]() -> int {
        const auto horz_freq = horizontal_frequencies({lo0, lo1});
        return *min_element(cbegin(horz_freq), cend(horz_freq));
    }();

    const auto M = [&]() -> int {
        const auto horz_freq = horizontal_frequencies({hi0, hi1});
        return *max_element(cbegin(horz_freq), cend(horz_freq));
    }();

    cout << m << ' ' << M << '\n';
    return 0;
}
