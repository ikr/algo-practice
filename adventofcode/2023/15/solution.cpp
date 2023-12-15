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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

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
    for (int i = 0; i < sz(box); ++i) {
        if (box[i].first == label) return i;
    }
    return -1;
}

int main() {
    string line;
    getline(cin, line);
    const auto tokens = split(",", line);

    vector<Box> boxes(256);

    const auto remove_lens = [&](const string &label) {
        auto &box = boxes[lhash(label)];
        const auto i = index_in_a_box(box, label);
        if (i != -1) box.erase(cbegin(box) + i);
    };

    const auto set_lens = [&](const string &label, const int flength) {
        const auto h = lhash(label);
        auto &box = boxes[h];
        const auto i = index_in_a_box(box, label);
        if (i != -1) {
            box[i].second = flength;
        } else {
            box.emplace_back(label, flength);
        }
    };

    for (const auto &t : tokens) {
        if (t.back() == '-') {
            const auto label = t.substr(0, sz(t) - 1);
            cerr << "remove " << label << endl;
            remove_lens(label);
        } else {
            const auto parts = split("=", t);
            const auto label = parts[0];
            const auto flength = stoi(parts[1]);
            cerr << "Set " << label << " to " << flength << endl;
            set_lens(label, flength);
        }
    }

    long long result{};
    for (int ib = 0; ib < sz(boxes); ++ib) {
        for (int il = 0; il < sz(boxes[ib]); ++il) {
            const auto cur = (ib + 1) * (il + 1) * boxes[ib][il].second;
            result += cur;
        }
    }
    cout << result << '\n';
    return 0;
}
