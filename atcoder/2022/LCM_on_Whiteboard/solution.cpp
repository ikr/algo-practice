#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using pii = pair<int, int>;

int lcms_num(const vector<vector<pii>> &pes) {
    map<int, int> e_hi;
    map<int, int> e_hi_fq;

    for (const auto &pe : pes) {
        for (const auto &[p, e] : pe) {
            if (e_hi.count(p)) {
                if (e_hi[p] == e) {

                } else if (e_hi[p] < e) {

                } else {
                    assert(e_hi[p] > e);
                }
            } else {
            }
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<vector<pii>> pes;
    pes.reserve(N);

    for (int i = 0; i < N; ++i) {
        int m;
        cin >> m;

        vector<pii> pe(m);
        for (auto &[p, e] : pe) {
            cin >> p >> e;
        }
        pes.push_back(pe);
    }

    cout << lcms_num(pes) << '\n';
    return 0;
}
