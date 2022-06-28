#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

array<vector<int>, AZ> letter_count_prefix_sums(const string &xs) {
    const auto N = sz(xs);
    array<vector<int>, AZ> pref{};
    pref.fill(vector(N, 0));

    for (int i = 0; i < N; ++i) {
        if (i) {
            for (int j = 0; j < AZ; ++j) {
                pref[j][i] = pref[j][i - 1];
            }
        }
        ++pref[inof(xs[i]) - inof('A')][i];
    }

    return pref;
}

int yeses_num(const string &xs, const vector<pii> &LR) {
    const auto pref = letter_count_prefix_sums(xs);

    const auto freq = [&](const int x, const int L, const int R) -> int {
        return pref[x][R] - (L ? pref[x][L - 1] : 0);
    };

    const auto freqs = [&](const int L, const int R) -> array<int, AZ> {
        array<int, AZ> result{};
        for (int x = 0; x < AZ; ++x) {
            result[x] = freq(x, L, R);
        }
        return result;
    };

    int result{};
    for (const auto &[L, R] : LR) {
        const auto fs = freqs(L, R);
        const auto odds = count_if(cbegin(fs), cend(fs),
                                   [](const int x) -> bool { return x % 2; });
        result += (odds <= 1);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, Q;
        cin >> N >> Q;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        vector<pii> LR(Q);
        for (auto &[L, R] : LR) {
            cin >> L >> R;
            --L;
            --R;
        }

        cout << "Case #" << i << ": " << yeses_num(xs, LR) << '\n';
    }

    return 0;
}
