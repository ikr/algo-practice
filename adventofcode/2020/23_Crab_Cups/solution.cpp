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

list<int> poke_one(const list<int> &xs) {
    const auto it = find(cbegin(xs), cend(xs), 1);
    list<int> ans;
    ans.insert(cend(ans), next(it), cend(xs));
    ans.insert(cend(ans), cbegin(xs), it);
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

    cout << join(xs) << '\n';
    cout << join(poke_one(xs)) << '\n';
    return 0;
}
