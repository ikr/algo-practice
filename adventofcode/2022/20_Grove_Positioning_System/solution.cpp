#include <bits/stdc++.h>
using namespace std;

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

using ll = long long;
using KeyVal = pair<int, ll>;

static constexpr ll MULTIPLIER = 811589153LL;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<KeyVal> key_values(const vector<ll> &xs) {
    vector<KeyVal> result(sz(xs));
    for (int i = 0; i < sz(xs); ++i) result[i] = KeyVal{i, xs[i]};
    return result;
}

int index_of(const vector<KeyVal> &kvs, const int key) {
    const auto it = find_if(cbegin(kvs), cend(kvs),
                            [key](const KeyVal kv) { return kv.first == key; });
    assert(it != cend(kvs));
    return inof(distance(cbegin(kvs), it));
}

vector<ll> only_values(const vector<KeyVal> &kvs) {
    vector<ll> result(sz(kvs));
    transform(cbegin(kvs), cend(kvs), begin(result),
              [](const KeyVal kv) { return kv.second; });
    return result;
}

vector<KeyVal> move_left(vector<KeyVal> kvs, const int key, const ll d) {
    ll i0 = index_of(kvs, key);
    const auto value = kvs[i0].second;

    kvs.erase(cbegin(kvs) + i0);

    i0 -= d;
    i0 %= 0LL + sz(kvs);
    i0 += sz(kvs);
    i0 %= 0LL + sz(kvs);

    if (i0 == 0LL) {
        kvs.emplace_back(key, value);
    } else {
        kvs.emplace(cbegin(kvs) + i0, key, value);
    }

    return kvs;
}

vector<KeyVal> move_right(vector<KeyVal> kvs, const int key, const ll d) {
    ll i0 = index_of(kvs, key);
    const auto value = kvs[i0].second;

    kvs.erase(cbegin(kvs) + i0);
    if (i0 == sz(kvs)) i0 = 0;

    i0 += d;
    i0 %= 0LL + sz(kvs);
    kvs.emplace(cbegin(kvs) + i0, key, value);

    return kvs;
}

vector<KeyVal> move_each_by_value(vector<KeyVal> kvs) {
    for (int i = 0; i < sz(kvs); ++i) {
        const auto x = kvs[index_of(kvs, i)].second;
        if (!x) continue;
        kvs = x < 0LL ? move_left(kvs, i, -x) : move_right(kvs, i, x);
    }
    return kvs;
}

int main() {
    vector<ll> xs;
    for (string line; getline(cin, line);) {
        xs.push_back(stoll(line) * MULTIPLIER);
    }

    cerr << xs << endl;
    auto kvs = key_values(xs);

    for (int i = 0; i < 10; ++i) {
        kvs = move_each_by_value(kvs);
        cerr << (i + 1) << ' ' << only_values(kvs) << endl;
    }

    xs = only_values(kvs);
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
