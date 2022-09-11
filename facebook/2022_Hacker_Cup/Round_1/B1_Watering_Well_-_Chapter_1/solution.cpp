#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint1000000007;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

mint solution(const vector<pii> &trees, const vector<pii> &wells) {
    unordered_map<int, int> a_fq;
    unordered_map<int, int> b_fq;
    for (const auto &[a, b] : trees) {
        ++a_fq[a];
        ++b_fq[b];
    }

    unordered_map<int, int> x_fq;
    unordered_map<int, int> y_fq;
    for (const auto &[x, y] : wells) {
        ++x_fq[x];
        ++y_fq[y];
    }

    mint result;

    for (const auto &[x, n] : x_fq) {
        for (const auto &[a, k] : a_fq) {
            result += mint{x - a}.pow(2) * n * k;
        }
    }

    for (const auto &[y, n] : y_fq) {
        for (const auto &[b, k] : b_fq) {
            result += mint{y - b}.pow(2) * n * k;
        }
    }

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
