#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const string Alpha{"J23456789TQKA"};

int card_index(const char x) {
    const auto i = Alpha.find(x);
    assert(i != string::npos);
    return inof(i);
}

enum class HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

HandType hand_type(const string &hand) {
    map<char, int> freqs;
    for (const auto c : hand) ++freqs[c];
    if (sz(freqs) == 1) return HandType::FIVE_OF_A_KIND;

    vector<int> fs;
    for (const auto [_, f] : freqs) fs.push_back(f);
    ranges::sort(fs);

    assert(accumulate(cbegin(fs), cend(fs), 0) == 5);

    if (fs == vector{1, 4}) return HandType::FOUR_OF_A_KIND;
    if (fs == vector{2, 3}) return HandType::FULL_HOUSE;
    if (fs == vector{1, 1, 3}) return HandType::THREE_OF_A_KIND;
    if (fs == vector{1, 2, 2}) return HandType::TWO_PAIR;
    if (fs == vector{1, 1, 1, 2}) return HandType::ONE_PAIR;
    return HandType::HIGH_CARD;
}

HandType best_hand_type(const string &hand) {
    int js{};
    string without_js;
    for (const auto c : hand) {
        if (c == 'J') {
            ++js;
        } else {
            without_js.push_back(c);
        }
    }

    vector<string> opts;
    for (const char j : string{"23456789TQKA"}) {
        const auto cur = without_js + string(js, j);
        opts.push_back(cur);
    }
    ranges::sort(opts, [](const auto &x, const auto &y) {
        return inof(hand_type(x)) < inof(hand_type(y));
    });
    return hand_type(opts.back());
}

vector<int> numeric_hand(const string &hand) {
    vector<int> ans(sz(hand));
    ranges::transform(hand, begin(ans), card_index);
    return ans;
}

vector<int> hand_ordinal(const string &hand) {
    auto result = numeric_hand(hand);
    result.insert(cbegin(result), inof(best_hand_type(hand)));
    return result;
}

int main() {
    vector<pair<string, int>> hands_with_bids;

    for (string line; getline(cin, line);) {
        const auto hand = line.substr(0, 5);
        const auto bid = stoi(line.substr(6));
        hands_with_bids.emplace_back(hand, bid);
    }

    ranges::sort(hands_with_bids, [](const auto &x, const auto &y) {
        return hand_ordinal(x.first) < hand_ordinal(y.first);
    });

    long long ans{};
    for (int i = 0; i < sz(hands_with_bids); ++i) {
        const auto rank = i + 1;
        const auto bid = hands_with_bids[i].second;
        ans += rank * bid;
    }
    cout << ans << '\n';
    return 0;
}
