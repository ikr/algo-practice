#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

int potential_princess_wins(vector<int> &ess, vector<int> &nce) {
    int result{};
    for (auto it = xbegin(ess); it != xend(ess) && !nce.empty();) {
        if (*it > nce.back()) {
            nce.pop_back();
            it = ess.erase(it);
            ++result;
            continue;
        }

        if (*it > nce.front()) {
            nce.erase(xbegin(nce));
            it = ess.erase(it);
            ++result;
            continue;
        }

        ++it;
    }
    return result;
}

int lowest_possible(const int i0, const set<int> &dealt) {
    for (int i = i0; i <= 52; ++i) {
        if (!dealt.count(i)) return i;
    }

    return -1;
}

int lowest_winning_card_to_deal_to_prince(vector<int> ess, vector<int> nce) {
    assert(sz(ess) == 3);
    assert(sz(nce) == 2);
    set<int> dealt(xbegin(ess), xend(ess));
    dealt.insert(xbegin(nce), xend(nce));
    assert(sz(dealt) == 5);

    const auto ess_pw = potential_princess_wins(ess, nce);
    if (ess_pw == 2) return -1;
    if (ess_pw == 0) return lowest_possible(1, dealt);

    assert(ess_pw == 1);
    return lowest_possible(ess.back() + 1, dealt);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    for (;;) {
        vector<int> ess(3);
        for (auto &a : ess) cin >> a;
        if (!ess[0]) break;
        sort(begin(ess), end(ess));

        vector<int> nce(2);
        for (auto &x : nce) cin >> x;
        sort(begin(nce), end(nce));

        cout << lowest_winning_card_to_deal_to_prince(ess, nce) << '\n';
    }

    return 0;
}
