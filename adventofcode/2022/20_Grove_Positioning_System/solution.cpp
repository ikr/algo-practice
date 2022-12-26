#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<pii> key_values(const vector<int> &xs) {
    vector<pii> result(sz(xs));
    for (int i = 0; i < sz(xs); ++i) result[i] = pii{i, xs[i]};
    return result;
}

int index_of(const vector<pii> &kvs, const int key) {
    const auto it = find_if(cbegin(kvs), cend(kvs),
                            [key](const pii kv) { return kv.first == key; });
    assert(it != cend(kvs));
    return inof(distance(cbegin(kvs), it));
}

vector<int> only_values(const vector<pii> &kvs) {
    vector<int> result(sz(kvs));
    transform(cbegin(kvs), cend(kvs), begin(result),
              [](const pii kv) { return kv.second; });
    return result;
}

vector<pii> move_left(vector<pii> kvs, const int key, const int d) {
    return kvs;
}

vector<pii> move_right(vector<pii> kvs, const int key, const int d) {
    return kvs;
}

vector<int> move_each_by_value(const vector<int> &xs) {
    auto kvs = key_values(xs);
    for (int i = 0; i < sz(xs); ++i) {
        const auto x = xs[i];
        kvs = x < 0 ? move_left(kvs, i, -x) : move_left(kvs, i, x);
    }
    return only_values(kvs);
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
