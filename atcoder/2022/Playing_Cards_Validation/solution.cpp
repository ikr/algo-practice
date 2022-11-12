#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const set<char> ONE{'H', 'D', 'C', 'S'};
static const set<char> TWO{'A', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'T', 'J', 'Q', 'K'};

bool satisfied(const vector<string> &xs) {
    if (all_of(cbegin(xs), cend(xs), [&](const auto &x) {
            return ONE.count(x[0]) && TWO.count(x[1]);
        })) {
        return sz(set(cbegin(xs), cend(xs))) == sz(xs);
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> xs(N);
    for (auto &x : xs) cin >> x;

    cout << (satisfied(xs) ? "Yes" : "No") << '\n';
    return 0;
}
