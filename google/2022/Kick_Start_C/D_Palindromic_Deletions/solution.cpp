#include <algorithm>
#include <atcoder/modint>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

using mint = atcoder::modint1000000007;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_pal(const string &xs) {
    if (sz(xs) < 2) return true;
    auto ys = xs;
    reverse(begin(ys), end(ys));
    return xs == ys;
}

mint solve(const string &xs0) {
    mint p{};
    mint q{};

    const auto recur = [&](const auto self, const string &xs,
                           const int carry) -> void {
        if (xs.empty()) {
            p += carry + 1;
            ++q;
            return;
        }

        for (int i = 0; i < sz(xs); ++i) {
            auto ys = xs;
            ys.erase(i, 1);
            self(self, ys, (!ys.empty() && is_pal(ys)) ? (carry + 1) : carry);
        }
    };

    recur(recur, xs0, 0);
    return p * q.inv();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << "Case #" << i << ": " << solve(xs).val() << '\n';
    }

    return 0;
}
