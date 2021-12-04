#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

vector<int> parse_drawn_numbers(const string &src) {
    const auto terms = split(regex(","), src);
    vector<int> result(sz(terms));
    transform(cbegin(terms), cend(terms), begin(result),
              [](const auto &t) { return stoi(t); });
    return result;
}

static constexpr int SZ = 5;

using Card = array<array<int, SZ>, SZ>;
using State = array<array<bool, SZ>, SZ>;

struct Location final {
    int card_index;
    int row;
    int column;
};

void line_input_done() {
    string s;
    getline(cin, s);
}

multimap<int, Location> build_index(const vector<Card> &cards) {
    multimap<int, Location> result;

    for (int i = 0; i < sz(cards); ++i) {
        for (int ro = 0; ro < SZ; ++ro) {
            for (int co = 0; co < SZ; ++co) {
                result.emplace(cards[i][ro][co], Location{i, ro, co});
            }
        }
    }

    return result;
}

bool has_row_just_won(const State &st, const int ro) {
    return count(cbegin(st[ro]), cend(st[ro]), true) == sz(st[ro]);
}

bool has_column_just_won(const State &st, const int co) {
    int k{};
    for (int ro = 0; ro < sz(st); ++ro) {
        if (st[ro][co]) ++k;
    }
    return k == sz(st);
}

bool has_just_won(const State &st, const int ro, const int co) {
    return has_row_just_won(st, ro) || has_column_just_won(st, co);
}

int winning_score(const int last_drawn_number, const Card &card,
                  const State &st) {
    int unmarked_total{};
    for (int ro = 0; ro < SZ; ++ro) {
        for (int co = 0; co < SZ; ++co) {
            if (!st[ro][co]) {
                unmarked_total += card[ro][co];
            }
        }
    }
    return unmarked_total * last_drawn_number;
}

int winning_score(const vector<Card> &cards, const vector<int> &drawn_numbers) {
    const auto idx = build_index(cards);
    vector<State> states(sz(cards), State{});
    set<int> cards_won;

    for (const auto x : drawn_numbers) {
        const auto [first, last] = idx.equal_range(x);

        for (auto it = first; it != last; ++it) {
            const auto l = it->second;
            states[l.card_index][l.row][l.column] = true;

            if (!cards_won.count(l.card_index) &&
                has_just_won(states[l.card_index], l.row, l.column)) {
                cards_won.insert(l.card_index);

                if (sz(cards_won) == sz(cards)) {
                    return winning_score(x, cards[l.card_index],
                                         states[l.card_index]);
                }
            }
        }
    }

    return -1;
}

int main() {
    string drawn_numbers_src;
    cin >> drawn_numbers_src;
    line_input_done();

    const auto drawn_numbers = parse_drawn_numbers(drawn_numbers_src);

    vector<Card> cards;

    for (;;) {
        {
            string sep;
            if (!getline(cin, sep)) break;
        }

        Card card;

        for (int ro = 0; ro < SZ; ++ro) {
            for (int co = 0; co < SZ; ++co) {
                cin >> card[ro][co];
            }
            line_input_done();
        }

        cards.push_back(card);
    }

    cout << winning_score(cards, drawn_numbers) << '\n';
    return 0;
}
