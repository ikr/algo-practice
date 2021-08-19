#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int AZ = inof('z') - inof('a') + 1;

string removal_seq(const string &t) {
    vector<bool> seen(AZ, false);
    string ans;

    for (auto it = crbegin(t); it != crend(t); ++it) {
        const int i = inof(*it) - inof('a');

        if (!seen[i]) {
            seen[i] = true;
            ans.push_back(*it);
        }
    }

    reverse(begin(ans), end(ans));
    return ans;
}

array<int, AZ> freqs(const string &t) {
    array<int, AZ> ans{};
    for (const auto x : t) {
        ++ans[inof(x) - inof('a')];
    }
    return ans;
}

optional<vi> positional_s_freqs(const string &xs, const string &t) {
    const auto fs = freqs(t);
    vi ans(sz(xs), 0);

    for (int i = 0; i < sz(xs); ++i) {
        const auto mul = i + 1;
        const auto x = xs[i];
        const auto f = fs[inof(x) - 'a'];

        if (f % mul) return nullopt;
        ans[i] = f / mul;
    }

    return ans;
}

array<int, AZ> absolutize(const string &xs, const vi &positional_fs) {
    array<int, AZ> ans{};
    for (int i = 0; i < sz(xs); ++i) {
        ans[inof(xs[i]) - inof('a')] = positional_fs[i];
    }
    return ans;
}

bool verify(string s, const string &xs, const string &t) {
    string buf;
    for (const auto x : xs) {
        buf += s;
        s.erase(remove(begin(s), end(s), x), end(s));
    }

    return buf == t;
}

pair<string, string> s_and_removal_seq(const string &t) {
    const auto nope = pair{string{""}, string{""}};
    const auto xs = removal_seq(t);

    const auto positional_fs_box = positional_s_freqs(xs, t);
    if (!positional_fs_box) return nope;
    const auto fs = absolutize(xs, *positional_fs_box);

    array<int, AZ> curr{};
    int i = 0;
    for (; i < sz(t); ++i) {
        ++curr[inof(t[i]) - inof('a')];
        if (curr == fs) break;
    }

    const auto s = t.substr(0, i + 1);
    return verify(s, xs, t) ? pair{s, xs} : nope;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        string t;
        cin >> t;

        const auto [s, xs] = s_and_removal_seq(t);
        if (xs.empty()) {
            cout << "-1\n";
        } else {
            cout << s << ' ' << xs << '\n';
        }
    }

    return 0;
}
