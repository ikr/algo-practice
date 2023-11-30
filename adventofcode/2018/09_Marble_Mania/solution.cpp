#include <bits/stdc++.h>
using namespace std;

using iter = list<int>::const_iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> static_re_matches(const string &pattern_str,
                                 const string &input) {
    static const regex pattern{pattern_str};
    smatch m;
    regex_match(input, m, pattern);
    assert(!empty(m));

    vector<string> result(size(m) - 1);
    transform(cbegin(m) + 1, cend(m), begin(result),
              [](const auto &x) { return x.str(); });
    return result;
}

int winning_score(const int players, const int last_marble) {
    list<int> circle{0};

    const auto step_cw = [&](const iter i) -> iter {
        assert(!empty(circle));
        assert(i != cend(circle));
        return next(i) == cend(circle) ? cbegin(circle) : next(i);
    };

    const auto step_ccw = [&](const iter i) -> iter {
        assert(!empty(circle));
        assert(i != cend(circle));
        return i == cbegin(circle) ? prev(cend(circle)) : prev(i);
    };

    const auto insert_before = [&](const iter i, const int x) -> iter {
        assert(!empty(circle));
        assert(i != cend(circle));
        return i == cbegin(circle) ? circle.insert(cend(circle), x)
                                   : circle.insert(i, x);
    };

    const auto erase_at = [&](const iter i) -> iter {
        assert(!empty(circle));
        assert(i != cend(circle));
        const auto i_ = circle.erase(i);
        return i_ == cend(circle) ? cbegin(circle) : i_;
    };

    vector<int> score(players, 0);
    iter i = cbegin(circle);

    for (int marble = 1; marble <= last_marble; ++marble) {
        if (marble % 23) {
            i = insert_before(step_cw(step_cw(i)), marble);
        } else {
            const auto player = (marble - 1) % players;
            score[player] += marble;

            for (int j = 0; j < 7; ++j) i = step_ccw(i);
            score[player] += *i;
            i = erase_at(i);
        }
    }

    return *ranges::max_element(score);
}

int main() {
    string input;
    getline(cin, input);

    const auto tokens = static_re_matches(
        R"(^(\d+) players; last marble is worth (\d+) points$)", input);
    const auto players = stoi(tokens[0]);
    const auto last_marble = stoi(tokens[1]);
    cout << winning_score(players, last_marble) << '\n';
    return 0;
}
