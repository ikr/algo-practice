#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using Mint = atcoder::modint1000000007;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi gather_milestones(const string &xs) {
    vi ans;

    const auto it0 =
        find_if(cbegin(xs), cend(xs), [](const char x) { return x != 'F'; });

    if (it0 == cend(xs)) return ans;
    ans.push_back(inof(distance(cbegin(xs), it0)));

    for (auto it = it0;;) {
        it = find_if(next(it), cend(xs),
                     [&](const char x) { return x != 'F' && x != *it; });

        if (it == cend(xs)) break;
        ans.push_back(inof(distance(cbegin(xs), it)));
    }

    cerr << ans << endl;

    return ans;
}

int solution(const string &xs) {
    const auto ms = gather_milestones(xs);
    Mint ans = 0;

    for (int i = 1; i < sz(ms); ++i) {
        const Mint a{ms[i - 1] + 1};
        const Mint b{sz(xs) - ms[i]};
        ans += a * b;
    }

    return ans.val();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        string xs(n, ' ');
        cin >> xs;

        cout << "Case #" << i << ": " << solution(xs) << '\n';
    }

    return 0;
}
