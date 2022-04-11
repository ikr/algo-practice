#include <iostream>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> gen_seq(const int N) {
    vector<int> ans((1 << N) - 1, 0);

    const auto recur = [&ans](const auto self, const int n, const int l,
                              const int r) -> void {
        if (!n) return;
        const auto W = r - l + 1;
        ans[l + W / 2] = n;

        self(self, n - 1, l, l + W / 2 - 1);
        self(self, n - 1, l + W / 2 + 1, r);
    };

    recur(recur, N, 0, sz(ans) - 1);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    cout << gen_seq(N) << '\n';
    return 0;
}
