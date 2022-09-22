#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string max_expression(const string &xs) {
    int pls{};
    int mns{};
    string ds;
    ds.reserve(sz(xs) / 2);

    for (const auto x : xs) {
        switch (x) {
        case '+':
            ++pls;
            break;

        case '-':
            ++mns;
            break;

        default:
            assert(inof('0') <= x && x <= inof('9'));
            ds += x;
        }
    }

    sort(begin(ds), end(ds));
    string result;
    result.reserve(sz(xs));

    for (int i = 0; i < mns; ++i) {
        result += ds[i];
        result += '-';
    }

    for (int i = 0; i < pls; ++i) {
        result += ds[mns + i];
        result += '+';
    }

    if (mns + pls < sz(ds)) result += ds.substr(mns + pls);

    reverse(begin(result), end(result));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << max_expression(xs) << '\n';
    }

    return 0;
}
