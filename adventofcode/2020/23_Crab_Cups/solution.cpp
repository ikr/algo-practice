#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const list<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

list<int> rotate_to(const list<int> &xs, const int t) {
    const auto it = find(cbegin(xs), cend(xs), t);
    list<int> ans;
    ans.insert(cend(ans), it, cend(xs));
    ans.insert(cend(ans), cbegin(xs), it);
    return ans;
}

constexpr int cyc_dec(const int x) { return x - 1 ? x - 1 : 9; }

int destination(const int current, const vector<int> &stash) {
    set<int> abc(cbegin(stash), cend(stash));

    int ans = cyc_dec(current);
    while (abc.count(ans)) ans = cyc_dec(ans);
    return ans;
}

vector<int> copy_to_stash(const list<int> &xs) {
    const auto first = next(cbegin(xs));
    auto last = first;
    advance(last, 3U);

    vector<int> ans(first, last);
    assert(ans.size() == 3U);
    return ans;
}

list<int> erase_stash(list<int> xs) {
    const auto first = next(cbegin(xs));
    auto last = first;
    advance(last, 3U);
    assert(distance(first, last) == 3U);

    xs.erase(first, last);
    return xs;
}

list<int> make_move(const list<int> &xs) {
    const auto stash = copy_to_stash(xs);
    auto ys = erase_stash(xs);
    const int dest = destination(xs.front(), stash);

    cout << "dest:" << dest << '\n';

    const auto dest_it = find(cbegin(ys), cend(ys), dest);
    ys.insert(next(dest_it), cbegin(stash), cend(stash));
    return rotate_to(ys, *next(cbegin(ys)));
}

list<int> poke_one(const list<int> &xs) {
    auto ans = rotate_to(xs, 1);
    ans.pop_front();
    return ans;
}

string join(const list<int> &xs) {
    return accumulate(cbegin(xs), cend(xs), string{},
                      [](string agg, const int x) {
                          agg += to_string(x);
                          return agg;
                      });
}

int main() {
    string s;
    cin >> s;

    list<int> xs(s.size(), 0);
    transform(cbegin(s), cend(s), begin(xs),
              [](const char d) { return d - '0'; });

    cout << make_move(xs) << '\n';
    return 0;
}
