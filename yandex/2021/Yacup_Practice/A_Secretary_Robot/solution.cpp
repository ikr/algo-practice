#include <bits/stdc++.h>
using namespace std;

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
    // D[i][j] is the minimal number of key presses up to index i, so that we
    // end up with the case j mode
    vector<array<int, 2>> D(sz(xs), array{INF, INF});

    switch (classify(xs[0])) {
    case Symb::SP:
    case Symb::LC:
        D[0][inof(Case::LO)] = 1;
        D[0][inof(Case::UP)] = 3;
        break;
    case Symb::UC:
        D[0][inof(Case::LO)] = 2;
        D[0][inof(Case::UP)] = 3;
        break;
    }

    for (int i = 1; i < sz(xs); ++i) {
        switch (classify(xs[i])) {
        case Symb::SP:
            D[i][inof(Case::LO)] = D[i - 1][inof(Case::LO)] + 1;
            D[i][inof(Case::UP)] = D[i - 1][inof(Case::UP)] + 1;
            break;
        case Symb::LC:
            D[i][inof(Case::LO)] =
                min(D[i - 1][inof(Case::LO)] + 1, D[i - 1][inof(Case::UP)] + 3);
            D[i][inof(Case::UP)] =
                min(D[i - 1][inof(Case::LO)] + 3, D[i - 1][inof(Case::UP)] + 2);
            break;
        case Symb::UC:
            D[i][inof(Case::LO)] =
                min(D[i - 1][inof(Case::LO)] + 2, D[i - 1][inof(Case::UP)] + 3);
            D[i][inof(Case::UP)] =
                min(D[i - 1][inof(Case::LO)] + 3, D[i - 1][inof(Case::UP)] + 1);
            break;
        }
    }

    return *min_element(cbegin(D.back()), cend(D.back()));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    getline(cin, xs);
    cout << min_key_presses(xs) << '\n';

    return 0;
}
