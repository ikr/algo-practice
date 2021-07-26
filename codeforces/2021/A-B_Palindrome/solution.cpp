#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string solution(const int total_a, const int total_b, string xs) {
    const int actual_a = inof(count(cbegin(xs), cend(xs), '0'));
    const int actual_b = inof(count(cbegin(xs), cend(xs), '1'));

    int a = total_a - actual_a;
    int b = total_b - actual_b;

    if (a < 0 || b < 0) return "-1";

    for (int i = 0; i < sz(xs) / 2; ++i) {
        const int l = i;
        const int r = sz(xs) - 1 - i;

        if (xs[l] != '?' && xs[r] != '?') {
            if (xs[l] != xs[r]) return "-1";
            continue;
        }

        if (xs[l] == '?' && xs[r] == '?') continue;

        if (xs[l] != '?') {
            assert(xs[r] == '?');
            if ((xs[l] == '0' && !a) || (xs[l] == '1' && !b)) return "-1";

            if (xs[l] == '0') {
                xs[r] = '0';
                --a;
            } else {
                assert(xs[l] == '1');
                xs[r] = '1';
                --b;
            }

            continue;
        }

        if (xs[r] != '?') {
            assert(xs[l] == '?');
            if ((xs[r] == '0' && !a) || (xs[r] == '1' && !b)) return "-1";

            if (xs[r] == '0') {
                xs[l] = '0';
                --a;
            } else {
                assert(xs[r] == '1');
                xs[l] = '1';
                --b;
            }
        }
    }

    for (int i = 0; i < sz(xs) / 2; ++i) {
        const int l = i;
        const int r = sz(xs) - 1 - i;
        assert((xs[l] == '?') == (xs[r] == '?'));
        if (xs[l] != '?' && xs[r] != '?') continue;

        if (a < 2 && b < 2) return "-1";

        if (a > b) {
            xs[l] = '0';
            xs[r] = '0';
            a -= 2;
        } else {
            xs[l] = '1';
            xs[r] = '1';
            b -= 2;
        }
    }

    const int m = sz(xs) / 2;
    if (sz(xs) % 2 && xs[m] == '?') {
        if (!a && !b) return "-1";

        if (a > b) {
            xs[m] = '0';
            --a;
        } else {
            xs[m] = '1';
            --b;
        }
    }

    return (!a && !b) ? xs : string{"-1"};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        string xs;
        cin >> xs;

        cout << solution(a, b, xs) << '\n';
    }

    return 0;
}
