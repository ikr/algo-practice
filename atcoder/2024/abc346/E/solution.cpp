#include <bits/stdc++.h>
using namespace std;

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

    int H, W, M;
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

    return 0;
}
