#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Pers { Mike, Josh, Nils };

ostream &operator<<(ostream &os, const Pers &x) {
    switch (x) {
    case Pers::Mike:
        os << "Mike";
        break;

    case Pers::Josh:
        os << "Josh";
        break;

    case Pers::Nils:
        os << "Nils";
        break;
    }
    return os;
}

template <typename T1, typename T2, typename T3>
ostream &operator<<(ostream &os, const tuple<T1, T2, T3> &x) {
    const auto [a, b, c] = x;
    os << a << ' ' << b << ' ' << c;
    return os;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

ll left_skew(const vector<ll> &xs) {
    const auto n = sz(xs);
    vector<ll> ss(n);
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto A = ss[n / 2 - 1];
    const auto B = ss.back() - ss[div_ceil(n, 2) - 1];
    return A - B;
}

tuple<Pers, Pers, Pers> locate_people(const array<vector<ll>, 3> &src) {
    auto xss = src;

    for (int i = 0; i < sz(src[0]); ++i) {
        const auto lo = min({src[0][i], src[1][i], src[2][i]});

        for (int j = 0; j < 3; ++j) {
            xss[j][i] -= lo;
        }
    }

    const auto surely_mike = [&]() -> optional<int> {
        array<ll, 3> ts{};
        transform(cbegin(src), cend(src), begin(ts), [](const auto &ys) {
            return accumulate(cbegin(ys), cend(ys), 0LL);
        });

        if (ts[0] < ts[1] && ts[0] < ts[2]) return 0;
        if (ts[1] < ts[0] && ts[1] < ts[2]) return 1;
        if (ts[2] < ts[0] && ts[2] < ts[1]) return 2;
        return nullopt;
    }();

    if (surely_mike) {
        set<int> duet{0, 1, 2};
        duet.erase(*surely_mike);

        const auto a = *cbegin(duet);
        const auto b = *crbegin(duet);

        if (left_skew(xss[a]) >= left_skew(xss[b])) {
            const auto person_at = [&](const int j) -> Pers {
                if (j == a) return Pers::Josh;
                if (j == b) return Pers::Nils;
                return Pers::Mike;
            };

            return {person_at(0), person_at(1), person_at(2)};
        } else {
            const auto person_at = [&](const int j) -> Pers {
                if (j == a) return Pers::Nils;
                if (j == b) return Pers::Josh;
                return Pers::Mike;
            };

            return {person_at(0), person_at(1), person_at(2)};
        }
    }

    {
        array<ll, 3> sks{};
        for (int j = 0; j < 3; ++j) {
            sks[j] = left_skew(xss[j]);
        }

        const auto lo =
            inof(distance(cbegin(sks), min_element(cbegin(sks), cend(sks))));

        const auto hi =
            inof(distance(cbegin(sks), max_element(cbegin(sks), cend(sks))));

        const auto person_at = [&](const int j) -> Pers {
            if (hi == j) return Pers::Josh;
            if (lo == j) return Pers::Nils;
            return Pers::Mike;
        };

        return {person_at(0), person_at(1), person_at(2)};
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        array<vector<ll>, 3> src;
        src.fill(vector<ll>(N, 0));

        for (auto &row : src) {
            for (auto &x : row) cin >> x;
        }

        cout << locate_people(src) << '\n';
    }

    return 0;
}
