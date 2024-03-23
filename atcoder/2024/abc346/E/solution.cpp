#include <bits/stdc++.h>
using namespace std;

using ll = long long;

enum class OpCode { Ro = 1, Co = 2 };

struct Op final {
    OpCode opcode;
    int i;
    int x;
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll H, W;
    int M;
    cin >> H >> W >> M;

    vector<Op> ops(M);
    for (auto &[opcode, i, x] : ops) {
        int t;
        cin >> t;
        opcode = static_cast<OpCode>(t);
        cin >> i >> x;
        --i;
    }
    reverse(begin(ops), end(ops));

    map<int, ll> fq;
    unordered_set<int> rows;
    unordered_set<int> cols;
    unordered_map<int, int> row_v;
    unordered_map<int, int> col_v;
    for (const auto &[opcode, i, x] : ops) {
        if (opcode == OpCode::Ro) {
            fq[x] += W - sz(cols);
            rows.insert(i);
        } else {
            assert(opcode == OpCode::Co);
            fq[x] += H - sz(rows);
            cols.insert(i);
        }
    }

    ll zs = H * W - accumulate(cbegin(fq), cend(fq), 0LL,
                               [](const ll acc, const auto &p) {
                                   return acc + p.second;
                               });
    if (zs) fq.emplace(0, zs);

    cout << sz(fq) << '\n';
    for (const auto &[c, x] : fq) {
        if (x) cout << c << ' ' << x << '\n';
    }
    return 0;
}
