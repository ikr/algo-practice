#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint component_solution(const vector<int> &A, const vector<int> &X) {
    mint sa;
    mint saa;
    for (const auto a : A) {
        sa += a;
        saa += mint{a}.pow(2);
    }

    mint sx;
    mint sxx;
    for (const auto x : X) {
        sx += x;
        sxx += mint{x}.pow(2);
    }

    mint result;
    result += sxx * sz(A);
    result += saa * sz(X);

    mint axs;
    for (const auto a : A) {
        axs += sx * a;
    }
    result += mint{-2} * axs;

    return result;
}

mint solution(const vector<pii> &trees, const vector<pii> &wells) {
    vector<int> A(sz(trees));
    vector<int> B(sz(trees));
    for (int i = 0; i < sz(trees); ++i) {
        A[i] = trees[i].first;
        B[i] = trees[i].second;
    }

    vector<int> X(sz(wells));
    vector<int> Y(sz(wells));
    for (int i = 0; i < sz(wells); ++i) {
        X[i] = wells[i].first;
        Y[i] = wells[i].second;
    }

    mint result;
    result += component_solution(A, X);
    result += component_solution(B, Y);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<pii> trees(N);
        for (auto &[a, b] : trees) cin >> a >> b;

        int Q;
        cin >> Q;

        vector<pii> wells(Q);
        for (auto &[x, y] : wells) cin >> x >> y;

        cout << "Case #" << i << ": " << solution(trees, wells).val() << '\n';
    }

    return 0;
}
