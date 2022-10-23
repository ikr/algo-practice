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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using tri = tuple<int, int, int>;

pair<int, int> solution(const vector<tri> &src, const int U) {
    const auto N = sz(src);
    vector<vector<int>> D(N, vector(U + 1, -1));

    {
        const auto [a, b, x] = src[0];
        int u = U;
        int k = 1;

        while (u >= a) {
            D[0][u - a + b] = k * x;
            u = u - a + b;
            ++k;
        }
    }

    cerr << "D0:\n" << D << endl;

    for (int i = 1; i < N; ++i) {
        const auto [a, b, x] = src[i];

        {
            int u = U;
            int k = 1;

            while (u >= a) {
                D[i][u - a + b] = k * x;
                u = u - a + b;
                ++k;
            }
        }

        for (int u0 = 0; u0 <= U; ++u0) {
            if (D[i - 1][u0] >= 0 && u0 >= a) {

                int u = u0;
                int k = 1;

                while (u >= a) {
                    cerr << "i:" << i << " u0:" << u0
                         << " prev:" << D[i - 1][u0] << " k:" << k
                         << " o1:" << D[i][u - a + b]
                         << " o2:" << (D[i - 1][u0] + k * x) << endl;

                    D[i][u - a + b] =
                        max(D[i][u - a + b], D[i - 1][u0] + k * x);
                    u = u - a + b;
                    ++k;
                }
            }
        }
    }

    cerr << "\nD:\n" << D << endl;

    int reward{};
    int energy = U;

    for (int j = 0; j < sz(D.back()); ++j) {
        if (D.back()[j] >= reward) {
            reward = D.back()[j];
            energy = j;
        }
    }

    return {reward, energy};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, U;
    cin >> N >> U;

    vector<tri> src(N);
    for (auto &[a, b, x] : src) cin >> a >> b >> x;

    const auto [reward, energy] = solution(src, U);
    cout << reward << ' ' << energy << '\n';
    return 0;
}
