#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string tanyas_plus(string a, string b) {
    string ans{};

    while (sz(a) < sz(b)) a = "0" + a;
    while (sz(b) < sz(a)) b = "0" + b;

    for (auto it = crbegin(a), jt = crbegin(b);
         it != crend(a) && jt != crend(b); ++it, ++jt) {
        const int x = inof(*it) - inof('0') + inof(*jt) - inof('0');
        ans = to_string(x) + ans;
    }

    // cerr << a << " t+ " << b << " t= " << ans << endl;
    return ans;
}

optional<ll> find_b(const string &a, const string &s) {
    string ans;

    int i = sz(a) - 1;
    int j = sz(s) - 1;

    while (j >= 0) {
        const int sub_a = i >= 0 ? inof(a[i]) - inof('0') : 0;

        {
            const int sub_s = inof(s[j]) - inof('0');
            if (sub_s >= sub_a) {
                ans = to_string(sub_s - sub_a) + ans;
                --i;
                --j;
                continue;
            }
        }

        {
            if (j < 1) return nullopt;
            const int sub_s = stoi(s.substr(j - 1, 2));

            if (sub_s >= sub_a) {
                ans = to_string(sub_s - sub_a) + ans;
                --i;
                j -= 2;
                continue;
            }
        }

        break;
    }

    return tanyas_plus(a, ans) == s ? optional{stoll(ans)} : nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string a, s;
        cin >> a >> s;

        const auto ans = find_b(a, s);
        cout << (ans ? *ans : -1LL) << '\n';
    }

    return 0;
}
