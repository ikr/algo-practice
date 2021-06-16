#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi phab_parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) cin >> phab_parent[i];

    vi ic(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> ic[i];

    int m;
    cin >> m;
    vvi diseases(m);
    for (auto &vs : diseases) {
        int cm;
        cin >> cm;
        vs.resize(cm);
        for (auto &v : vs) cin >> v;
    }

    int nq;
    cin >> nq;
    vvi patients(nq);
    for (auto &vs : patients) {
        int cq;
        cin >> cq;
        vs.resize(cq);
        for (auto &v : vs) cin >> v;
    }

    return 0;
}
