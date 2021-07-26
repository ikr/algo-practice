#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

enum class Op { AND, OR };

ll tuples_num(const vector<Op> &ops) {
    const int n = ops.size() + 1;
    vector<ll> dp_t(n, 1);

    for (int i = 1; i < n; ++i) {
        if (ops[i - 1] == Op::AND) {
            dp_t[i] = dp_t[i - 1];
        } else {
            const ll dp_f = (1LL << llof(i)) - dp_t[i - 1];
            dp_t[i] = dp_t[i - 1] * 2LL + dp_f;
        }
    }

    return dp_t.back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Op> ops(n);

    for (auto &op : ops) {
        string s;
        cin >> s;
        op = s == "OR" ? Op::OR : Op::AND;
    }

    cout << tuples_num(ops) << '\n';
    return 0;
}
