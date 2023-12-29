#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll num_greetings(vector<pii> AB) {
    vector<int> M;
    M.reserve(sz(AB) * 2);
    for (const auto &[a, b] : AB) {
        M.push_back(a);
        M.push_back(b);
    }
    ranges::sort(M);

    map<int, int> idx;
    for (int i = 0; i < sz(M); ++i) idx[M[i]] = i;

    ranges::sort(AB, [](const auto &lhs, const auto &rhs) {
        return lhs.second - lhs.first < rhs.second - rhs.first;
    });

    ll result{};
    atcoder::fenwick_tree<int> fw(sz(M));
    for (const auto &[a, b] : AB) {
        const auto i = idx.at(a);
        const auto j = idx.at(b);
        assert(i < j);

        cerr << a << " -> " << b << " met " << fw.sum(i, j)
             << " previously arrived" << endl;
        result += fw.sum(i, j);
        fw.add(j, 1);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<pii> AB(n);
        for (auto &[a, b] : AB) cin >> a >> b;
        cout << num_greetings(std::move(AB)) << '\n';
    }

    return 0;
}
