#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using mint = atcoder::modint;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

string maximal_X(const int N, const int M) {
    assert(mint{1} == mint{M + 1});

    mint sigma0{};
    for (int i = 0; i < N; ++i) {
        sigma0 += mint{10}.pow(i);
    }

    auto sigma = sigma0;
    for (int d = N; d >= 1; --d) {
        for (int a = 9; a >= 1; --a) {
            if (mint{a} * sigma == mint{0}) {
                const auto digit = chof(inof('0') + a);
                return string(d, digit);
            }
        }

        sigma -= mint{10}.pow(d - 1);
    }

    return "-1";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;
    mint::set_mod(M);

    cout << maximal_X(N, M) << '\n';
    return 0;
}
