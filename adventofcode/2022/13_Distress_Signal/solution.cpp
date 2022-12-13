#include "json.hpp"
#include <bits/stdc++.h>
using namespace std;

using Json = nlohmann::json;
using Iter = Json::const_iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool equal(const pair<Iter, Iter> suf_a, const pair<Iter, Iter> suf_b) {
    const auto [cur_a, end_a] = suf_a;
    const auto [cur_b, end_b] = suf_b;

    if (cur_a == end_a && cur_b == end_b) return true;
    if (cur_a == end_a) return false;
    if (cur_b == end_b) return false;

    if (cur_a->is_number() && cur_b->is_number()) {
        const auto x = cur_a->get<Json::number_integer_t>();
        const auto y = cur_b->get<Json::number_integer_t>();
        if (x != y) return false;
    } else if (cur_a->is_number()) {
        const auto a_ = Json::array({cur_a->get<Json::number_integer_t>()});
        if (!equal({cbegin(a_), cend(a_)}, {cur_b->cbegin(), cur_b->cend()})) {
            return false;
        }
    } else if (cur_b->is_number()) {
        const auto b_ = Json::array({cur_b->get<Json::number_integer_t>()});
        if (!equal({cur_a->cbegin(), cur_a->cend()}, {cbegin(b_), cend(b_)})) {
            return false;
        }
    } else {
        assert(cur_a->is_array() && cur_b->is_array());
        if (!equal({cur_a->cbegin(), cur_a->cend()},
                   {cur_b->cbegin(), cur_b->cend()})) {
            return false;
        }
    }

    return equal({next(cur_a), end_a}, {next(cur_b), end_b});
}

bool less_than(const pair<Iter, Iter> suf_a, const pair<Iter, Iter> suf_b) {
    const auto [cur_a, end_a] = suf_a;
    const auto [cur_b, end_b] = suf_b;

    if (cur_a == end_a) return cur_b != end_b;
    if (cur_b == end_b) return false;

    if (cur_a->is_number() && cur_b->is_number()) {
        const auto x = cur_a->get<Json::number_integer_t>();
        const auto y = cur_b->get<Json::number_integer_t>();
        if (x < y) return true;
        if (x > y) return false;
    } else if (cur_a->is_number()) {
        const auto a_ = Json::array({cur_a->get<Json::number_integer_t>()});
        if (less_than({cbegin(a_), cend(a_)},
                      {cur_b->cbegin(), cur_b->cend()})) {
            return true;
        }

        if (!equal({cbegin(a_), cend(a_)}, {cur_b->cbegin(), cur_b->cend()})) {
            return false;
        }
    } else if (cur_b->is_number()) {
        const auto b_ = Json::array({cur_b->get<Json::number_integer_t>()});
        if (less_than({cur_a->cbegin(), cur_a->cend()},
                      {cbegin(b_), cend(b_)})) {
            return true;
        }

        if (!equal({cur_a->cbegin(), cur_a->cend()}, {cbegin(b_), cend(b_)})) {
            return false;
        }
    } else {
        assert(cur_a->is_array() && cur_b->is_array());
        if (less_than({cur_a->cbegin(), cur_a->cend()},
                      {cur_b->cbegin(), cur_b->cend()})) {
            return true;
        }

        if (!equal({cur_a->cbegin(), cur_a->cend()},
                   {cur_b->cbegin(), cur_b->cend()})) {
            return false;
        }
    }

    return less_than({next(cur_a), end_a}, {next(cur_b), end_b});
}

int main() {
    vector<Json> xs{Json::parse("[[2]]"), Json::parse("[[6]]")};

    for (;;) {
        string line;
        getline(cin, line);
        xs.push_back(Json::parse(line));

        getline(cin, line);
        xs.push_back(Json::parse(line));

        if (!getline(cin, line)) break;
    }

    sort(begin(xs), end(xs), [](const auto &a, const auto &b) {
        return less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)});
    });

    for (const auto &x : xs) {
        cout << x << '\n';
    }

    return 0;
}
