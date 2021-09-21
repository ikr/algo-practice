#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const vector<array<T, N>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Symb { LC = 0, UC = 1, SP = 2 };
enum class Case { LO = 0, UP = 1 };

constexpr Symb classify(const char x) {
    if (x == ' ') return Symb::SP;
    return (inof('A') <= inof(x) && inof(x) <= inof('Z')) ? Symb::UC : Symb::LC;
}

constexpr int INF = 1e9;

int min_key_presses(const string &xs) {
    // tbl[i][j] is the minimal number of key presses up to index i, so that we
    // end up with the case j mode
    vector<array<int, 2>> tbl(sz(xs), array{INF, INF});

    switch (classify(xs[0])) {
    case Symb::SP:
    case Symb::LC:
        tbl[0][inof(Case::LO)] = 1;
        tbl[0][inof(Case::UP)] = 3;
        break;
    case Symb::UC:
        tbl[0][inof(Case::LO)] = 2;
        tbl[0][inof(Case::UP)] = 3;
        break;
    }

    for (int i = 1; i < sz(xs); ++i) {
        switch (classify(xs[i])) {
        case Symb::SP:
            tbl[i][inof(Case::LO)] = tbl[i - 1][inof(Case::LO)] + 1;
            tbl[i][inof(Case::UP)] = tbl[i - 1][inof(Case::UP)] + 1;
            break;
        case Symb::LC:
            tbl[i][inof(Case::LO)] = min(tbl[i - 1][inof(Case::LO)] + 1,
                                         tbl[i - 1][inof(Case::UP)] + 3);
            tbl[i][inof(Case::UP)] = min(tbl[i - 1][inof(Case::LO)] + 3,
                                         tbl[i - 1][inof(Case::UP)] + 2);
            break;
        case Symb::UC:
            tbl[i][inof(Case::LO)] = min(tbl[i - 1][inof(Case::LO)] + 2,
                                         tbl[i - 1][inof(Case::UP)] + 3);
            tbl[i][inof(Case::UP)] = min(tbl[i - 1][inof(Case::LO)] + 3,
                                         tbl[i - 1][inof(Case::UP)] + 1);
            break;
        }
    }

    // cerr << tbl << endl;
    return *min_element(cbegin(tbl.back()), cend(tbl.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    getline(cin, xs);
    cout << min_key_presses(xs) << '\n';

    return 0;
}
