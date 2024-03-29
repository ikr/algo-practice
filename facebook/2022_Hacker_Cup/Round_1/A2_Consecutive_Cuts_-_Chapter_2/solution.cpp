#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> bool has_one_unique_value(const T &xs) {
    return all_of(cbegin(xs) + 1, cend(xs),
                  [&](const auto a) { return a == xs.front(); });
}

// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/KMP.h
namespace kactl {
using vi = vector<int>;
vi pi(const vi &s) {
    vi p(sz(s));
    for (int i = 1; i < sz(s); ++i) {
        int g = p[i - 1];
        while (g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

vi match(const vi &s, const vi &pat) {
    vi p = pi([&]() -> vi {
        auto result = pat;
        result.push_back(INT_MIN);
        result.insert(cend(result), cbegin(s), cend(s));
        return result;
    }());

    vi res;

    for (int i = sz(p) - sz(s); i < sz(p); ++i) {
        if (p[i] == sz(pat)) {
            res.push_back(i - 2 * sz(pat));
        }
    }
    return res;
}
} // namespace kactl

bool is_possible(const int K, vector<int> A, vector<int> B) {
    if (K == 0) return A == B;

    if (A.size() == 2) {
        if (A == B) {
            return K % 2 == 0 || has_one_unique_value(A);
        } else {
            return K % 2 == 1;
        }
    }

    if (A == B) return K != 1 || has_one_unique_value(A);

    auto BB = B;
    BB.insert(cend(BB), cbegin(B), cend(B));
    return !kactl::match(BB, A).empty();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K;
        cin >> N >> K;

        vector<int> A(N);
        for (auto &a : A) cin >> a;

        vector<int> B(N);
        for (auto &b : B) cin >> b;

        cout << "Case #" << i << ": "
             << (is_possible(K, move(A), move(B)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
