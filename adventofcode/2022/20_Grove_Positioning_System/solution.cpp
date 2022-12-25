#include <bits/stdc++.h>
using namespace std;

using Iter = list<int>::const_iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<list<int>, vector<Iter>>
values_list_and_its_iterators(const vector<int> &xs) {
    list<int> li;
    vector<Iter> it(sz(xs));

    for (int i = 0; i < sz(xs); i++) {
        it[i] = li.insert(cend(li), xs[i]);
        cerr << "it[i]:" << *it[i] << endl;
    }

    return {li, it};
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<int> move_each_by_value(const vector<int> &xs) {
    auto liit = values_list_and_its_iterators(xs);
    auto &li = liit.first;
    const auto &it = liit.second;

    const auto step_left = [&](const Iter i) -> Iter {
        return i == cbegin(li) ? prev(cend(li)) : prev(i);
    };

    const auto step_right = [&](const Iter i) -> Iter {
        return next(i) == cend(li) ? cbegin(li) : next(i);
    };

    for (const auto &i : it) {
        cerr << "li: " << vector(cbegin(li), cend(li)) << " x:" << *i << endl;
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
            li.insert(next(j) == cend(li) ? cend(li) : next(j), x);
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

    const auto [hi, lo] = minmax_element(cbegin(xs), cend(xs));
    cerr << *hi << ' ' << *lo << endl;

    cerr << move_each_by_value(xs) << endl;
    return 0;
}
