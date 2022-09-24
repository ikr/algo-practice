#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

using Freqs = array<int, AZ>;

constexpr Freqs zeros() {
    Freqs result{};
    result.fill(0);
    return result;
}

constexpr int code(const char x) { return inof(x) - inof('a'); }

constexpr Freqs agg_minus(Freqs xs, const Freqs &ys) {
    for (int i = 0; i < sz(xs); ++i) {
        xs[i] -= ys[i];
    }
    return xs;
}

constexpr int manhattan(const Freqs &xs, const Freqs &ys) {
    int result{};
    for (int i = 0; i < sz(xs); ++i) {
        result += abs(xs[i] - ys[i]);
    }
    return result;
}

int solution(const string &xs, const vector<pii> &LR) {
    vector<Freqs> ss(sz(xs), zeros());
    ++ss[0][code(xs[0])];

    for (int i = 1; i < sz(xs); ++i) {
        ss[i] = ss[i - 1];
        ++ss[i][code(xs[i])];
    }

    const auto span = [&](const int a, const int b) -> Freqs {
        if (a == 0) return ss[b];
        return agg_minus(ss[b], ss[a - 1]);
    };

    int result{};
    for (const auto &[L, R] : LR) {
        if ((R - L + 1) % 2 == 0) continue;

        if (L == R) {
            ++result;
            continue;
        }

        const auto m = (L + R) / 2;
        result += manhattan(span(L, m), span(m + 1, R)) == 1 ||
                  manhattan(span(L, m - 1), span(m, R)) == 1;
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string xs;
        cin >> xs;

        int Q;
        cin >> Q;

        vector<pii> LR(Q);
        for (auto &[L, R] : LR) {
            cin >> L >> R;
            --L;
            --R;
            assert(L <= R);
        }

        cout << "Case #" << i << ": " << solution(xs, LR) << '\n';
    }

    return 0;
}
