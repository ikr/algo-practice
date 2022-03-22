#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int AZ = 26;

vector<int> encode(const string &s) {
    vector<int> first(AZ, 0);
    vector<int> result(sz(s), 0);

    for (int i = 0; i < sz(s); ++i) {
        const int curr = i + 1;
        const int j = inof(s[i]) - inof('a');

        if (!first[j]) {
            first[j] = curr;
        }

        result[i] = first[j];
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string s;
    cin >> s;
    assert(sz(s) == n);

    int Q;
    cin >> Q;

    const auto xs = encode(s);
    vector<int> ss(sz(xs), 0);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    for (int i = 1; i <= Q; ++i) {
        int L, R;
        cin >> L >> R;
        --L;
        --R;

        const int ans = L == 0 ? ss[R] : (ss[R] - ss[L - 1]);
        cout << ans << '\n';
    }

    return 0;
}
