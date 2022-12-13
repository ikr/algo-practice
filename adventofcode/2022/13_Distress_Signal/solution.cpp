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

int pairs_in_right_order_positions_sum(const vector<pair<Json, Json>> &ps) {
    int result{};

    for (int i = 0; i < sz(ps); ++i) {
        if (less_than({cbegin(ps[i].first), cend(ps[i].first)},
                      {cbegin(ps[i].second), cend(ps[i].second)})) {
            result += (i + 1);
        }
    }

    return result;
}

int main() {
    vector<pair<Json, Json>> ps;

    for (;;) {
        string line_a;
        getline(cin, line_a);

        string line_b;
        getline(cin, line_b);

        ps.emplace_back(Json::parse(line_a), Json::parse(line_b));

        if (!getline(cin, line_b)) break;
    }

    {
        const auto a = Json::parse("[1,1,3,1,1]");
        const auto b = Json::parse("[1,1,5,1,1]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[[1],[2,3,4]]");
        const auto b = Json::parse("[[1],4]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[9]");
        const auto b = Json::parse("[[8,7,6]]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(!less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[[4,4],4,4]");
        const auto b = Json::parse("[[4,4],4,4,4]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[7,7,7,7]");
        const auto b = Json::parse("[7,7,7]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(!less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[]");
        const auto b = Json::parse("[3]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[[[]]]");
        const auto b = Json::parse("[[]]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(!less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    {
        const auto a = Json::parse("[1,[2,[3,[4,[5,6,7]]]],8,9]");
        const auto b = Json::parse("[1,[2,[3,[4,[5,6,0]]]],8,9]");
        assert(!equal({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
        assert(!less_than({cbegin(a), cend(a)}, {cbegin(b), cend(b)}));
    }

    cout << pairs_in_right_order_positions_sum(ps) << '\n';
    return 0;
}
