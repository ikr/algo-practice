#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
constexpr static int INF = 1e9;

template <typename T> struct mmax {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

template <typename Iter, typename R, typename Binop1, typename Binop2>
R ttransform_reduce(Iter first1, Iter last1, Iter first2, R init, Binop1 binop1,
                    Binop2 binop2) {
    R ans = init;

    for (auto it = first1, jt = first2; it != last1; ++it, ++jt) {
        ans = binop1(ans, binop2(*it, *jt));
    }

    return ans;
}

vi rotate45(const vi &xs) {
    const int sz = xs.size();
    const int s = accumulate(cbegin(xs), cend(xs), 0);

    vi ans(sz + 1, s);
    for (int i = 1; i <= sz; ++i) ans[i] -= 2 * xs[i - 1];
    return ans;
}

vvi rotate45_(const vvi &xss) {
    vvi ans(xss.size());
    transform(cbegin(xss), cend(xss), begin(ans), rotate45);
    return ans;
}

int manh(const int x, const int y) { return abs(x - y); }

int manh_(const vi &xs, const vi &ys) {
    return ttransform_reduce(cbegin(xs), cend(xs), cbegin(ys), 0, plus<int>{},
                             manh);
}

int cheb(const vi &xs, const vi &ys) {
    return ttransform_reduce(cbegin(xs), cend(xs), cbegin(ys), -INF,
                             mmax<int>{}, manh);
}

void test_rotation(const vvi &xss) {
    const int n = xss.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cout << manh_(xss[i], xss[j]) << ' ';
        }
    }
    cout << '\n';

    const auto yss = rotate45_(xss);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            cout << cheb(yss[i], yss[j]) << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, D;
    cin >> N >> D;

    vvi xss(N, vi(D, 0));
    for (auto &xs : xss) {
        for (auto &x : xs) cin >> x;
    }

    test_rotation(xss);

    return 0;
}
