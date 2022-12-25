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

using Iter = list<int>::const_iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> move_each_by_value(const vector<int> &xs) {
    list<int> li;
    vector<Iter> it(sz(xs));

    for (int i = 0; i < sz(xs); i++) {
        it[i] = li.insert(cend(li), xs[i]);
    }

    const auto step_left = [&](const Iter i) -> Iter {
        return i == cbegin(li) ? prev(cend(li)) : prev(i);
    };

    const auto step_right = [&](const Iter i) -> Iter {
        return next(i) == cend(li) ? cbegin(li) : next(i);
    };

    for (const auto &i : it) {
        const auto x = *i;
        if (!x) continue;

        auto j = i;
        for (int k = 0; k < abs(x); ++k) {
            if (x < 0) {
                j = step_left(j);
            } else {
                j = step_right(j);
            }
        }

        if (x < 0) {
            li.insert(j == cbegin(li) ? cend(li) : j, x);
        } else {
            li.insert(next(j), x);
        }
        li.erase(i);
    }

    return vector(cbegin(li), cend(li));
}

int main() {
    vector<int> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(stoi(line));
    }

    xs = move_each_by_value(xs);
    cerr << xs << endl;

    const auto it_zero = find(cbegin(xs), cend(xs), 0);
    assert(it_zero != cend(xs));
    const auto iz = inof(distance(cbegin(xs), it_zero));

    const auto n = sz(xs);
    const auto a = xs[(iz + 1000) % n];
    const auto b = xs[(iz + 2000) % n];
    const auto c = xs[(iz + 3000) % n];

    cout << (a + b + c) << '\n';
    return 0;
}
