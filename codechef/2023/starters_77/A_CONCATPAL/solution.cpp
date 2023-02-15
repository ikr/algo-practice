#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    while (t--) {
        int N, M;
        cin >> N >> M;

        string A, B;
        cin >> A >> B;
        assert(sz(A) == N);
        assert(sz(B) == M);

        array<int, AZ> fs;
        fs.fill(0);

        for (const auto &xs : {A, B}) {
            for (const auto &c : xs) {
                const auto x = inof(c) - inof('a');
                ++fs[x];
            }
        }

        const auto odds =
            count_if(cbegin(fs), cend(fs), [](const int f) { return f % 2; });

        const auto yes = (odds <= 1);
        cout << (yes ? "YES" : "NO") << '\n';
    }
    return 0;
}
