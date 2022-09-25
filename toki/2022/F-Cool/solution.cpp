#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint998244353;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << i->val();
    }
    return os;
}

vector<mint> solution(const int N, const int F) { return vector<mint>(N, 0); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, F;
    cin >> N >> F;

    cout << solution(N, F) << '\n';
    return 0;
}
