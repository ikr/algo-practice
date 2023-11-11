#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

int next_letter(const array<set<int>, 3> &idx, const int i0) {
    vector<pair<int, int>> os;
    for (int l = 0; l < 3; ++l) {
        const auto it = idx[l].upper_bound(i0);
        if (it == cend(idx[l])) continue;
        os.emplace_back(*it, l);
    }
    ranges::sort(os);
    return empty(os) ? -1 : os[0].second;
}

bool apply_op(array<set<int>, 3> &idx) {
    bool reduced = false;
    for (auto it = cbegin(idx[0]); it != cend(idx[0]);) {
        if (next_letter(idx, *it) != 1) {
            ++it;
            continue;
        }
        const auto jt = idx[1].upper_bound(*it);
        assert(jt != cend(idx[1]));

        if (next_letter(idx, *jt) != 2) {
            ++it;
            continue;
        }
        const auto kt = idx[2].upper_bound(*jt);
        assert(kt != cend(idx[2]));

        it = idx[0].erase(it);
        if (!empty(idx[0]) && it != cbegin(idx[0])) --it;
        idx[1].erase(*jt);
        idx[2].erase(*kt);
        reduced = true;
    }

    return reduced;
}

string reconstruct(const array<set<int>, 3> &idx) {
    vector<pair<int, char>> ps;
    for (int i = 0; i < 3; ++i) {
        for (const auto x : idx[i]) {
            ps.emplace_back(x, chof('A' + i));
        }
    }
    ranges::sort(ps);

    string ans;
    ans.reserve(sz(ps));
    for (const auto &[_, c] : ps) ans.push_back(c);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    array<set<int>, 3> idx{};
    for (int i = 0; i < sz(xs); ++i) {
        idx[xs[i] - 'A'].insert(i);
    }

    for (;;) {
        if (!apply_op(idx)) break;
    }

    cout << reconstruct(idx) << '\n';
    return 0;
}
