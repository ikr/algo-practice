#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/RMQ.h
namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template <class T> struct RMQ_LO {
    vector<vector<T>> jmp;
    RMQ_LO(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k])) jmp[k][j] =
                min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

template <class T> struct RMQ_HI {
    vector<vector<T>> jmp;
    RMQ_HI(const vector<T> &V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k])) jmp[k][j] =
                max(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

} // namespace kactl

optional<int> min_ops(const vector<int> &xs) {
    auto lo = kactl::RMQ_LO(xs);
    auto hi = kactl::RMQ_HI(xs);

    const auto recur = [&](const auto self, const int a,
                           const int b) -> optional<int> {
        if (a == b) return 0;

        const auto m = a + (b - a) / 2;

        const auto a1 = a;
        const auto b1 = m;
        const auto a2 = m + 1;
        const auto b2 = b;

        const auto sub1 = self(self, a1, b1);
        if (!sub1) return nullopt;
        const auto sub2 = self(self, a2, b2);
        if (!sub2) return nullopt;

        const auto left_lo = lo.query(a1, b1 + 1);
        const auto left_hi = hi.query(a1, b1 + 1);

        const auto right_lo = lo.query(a2, b2 + 1);
        const auto right_hi = hi.query(a2, b2 + 1);

        if (left_hi + 1 == right_lo) {
            return *sub1 + *sub2;
        } else if (right_hi + 1 == left_lo) {
            return *sub1 + *sub2 + 1;
        }

        return nullopt;
    };

    return recur(recur, 0, sz(xs) - 1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        assert(__builtin_popcount(n) == 1);
        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        const auto result = min_ops(xs);
        cout << (result ? *result : -1) << '\n';
    }

    return 0;
}
