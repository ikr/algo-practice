#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int lhash(const string &xs) {
    int result{};
    for (const auto x : xs) {
        result += inof(x);
        result *= 17;
        result %= 256;
    }
    return result;
}

using Lens = pair<string, int>;
using Box = vector<Lens>;

int index_in_a_box(const Box &box, const string &label) {
    return inof(
        ranges::find_if(box,
                        [&](const auto &lens) { return lens.first == label; }) -
        cbegin(box));
}

int main() {
    string line;
    getline(cin, line);
    const auto tokens = split(",", line);

    vector<Box> boxes(256);

    const auto remove_lens = [&](const string &label) {
        auto &box = boxes[lhash(label)];
        const auto i = index_in_a_box(box, label);
        if (i != sz(box)) box.erase(cbegin(box) + i);
    };

    const auto set_lens = [&](const string &label, const int flength) {
        const auto h = lhash(label);
        auto &box = boxes[h];
        const auto i = index_in_a_box(box, label);
        if (i != sz(box)) {
            box[i].second = flength;
        } else {
            box.emplace_back(label, flength);
        }
    };

    for (const auto &t : tokens) {
        if (t.back() == '-') {
            const auto label = t.substr(0, sz(t) - 1);
            remove_lens(label);
        } else {
            const auto parts = split("=", t);
            const auto label = parts[0];
            const auto flength = stoi(parts[1]);
            set_lens(label, flength);
        }
    }

    int result{};
    for (int ib = 0; ib < sz(boxes); ++ib) {
        for (int il = 0; il < sz(boxes[ib]); ++il) {
            const auto cur = (ib + 1) * (il + 1) * boxes[ib][il].second;
            result += cur;
        }
    }
    cout << result << '\n';
    return 0;
}
