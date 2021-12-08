#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim, const string &s) {
    regex r(delim);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

string join(const string &glue, const vector<string> &tokens) {
    string ans;

    for (const auto &t : tokens) {
        if (!ans.empty()) ans += glue;
        ans += t;
    }

    return ans;
}

template <typename T> T number(const vector<int> &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

using Display = bitset<7>;
using Mapping = array<int, 7>;

int read_display(const Display d) {
    switch (inof(d.to_ulong())) {
    case 0b1110111:
        return 0;
    case 0b0100100:
        return 1;
    case 0b1011101:
        return 2;
    case 0b1101101:
        return 3;
    case 0b0101110:
        return 4;
    case 0b1101011:
        return 5;
    case 0b1111011:
        return 6;
    case 0b0100101:
        return 7;
    case 0b1111111:
        return 8;
    case 0b1101111:
        return 9;
    default:
        cerr << "d:" << d.to_ulong() << endl;
        assert(false && "Invalid display bits");
        return -1;
    }
}

Display decode(const Mapping &m, const string &code) {
    Display result;
    for (const auto x : code) {
        result[m[inof(x) - inof('a')]] = true;
    }
    return result;
}

map<int, vector<string>> group_by_length(const vector<string> &ivs) {
    map<int, vector<string>> result;
    for (const auto &iv : ivs) {
        result[sz(iv)].push_back(iv);
    }
    assert(sz(result[2]) == 1);
    assert(sz(result[3]) == 1);
    assert(sz(result[4]) == 1);
    assert(sz(result[5]) == 3);
    assert(sz(result[6]) == 3);
    assert(sz(result[7]) == 1);
    return result;
}

bool contains(const string &haystack, const char needle) {
    return haystack.find(needle) != haystack.npos;
}

string intersection(string ca, string cb) {
    sort(begin(ca), end(ca));
    sort(begin(cb), end(cb));
    string x;
    set_intersection(cbegin(ca), cend(ca), cbegin(cb), cend(cb),
                     back_inserter(x));
    return x;
}

string outside_intersection(const string &ca, const string &cb) {
    const auto x = intersection(ca, cb);

    set<char> result;
    for (const auto c : (ca + cb)) {
        if (contains(x, c)) continue;
        result.insert(c);
    }
    return string(cbegin(result), cend(result));
}

Mapping gather_freqs(const string &xs) {
    Mapping result{};
    for (const auto x : xs) {
        ++result[inof(x) - inof('a')];
    }
    return result;
}

Mapping deduce_mapping(const vector<string> &ivs) {
    // 6 2 5 5 4
    // 5 6 3 7 6
    const auto gbl = group_by_length(ivs);

    Mapping result;
    result.fill(-1);

    const string bits_2_5 = gbl.at(2)[0];
    const char bit_0_in = outside_intersection(bits_2_5, gbl.at(3)[0])[0];
    result[inof(bit_0_in) - inof('a')] = 0;

    const auto fs_6 = gather_freqs(join("", gbl.at(6)));
    const char bit_2_in =
        fs_6[inof(bits_2_5[0]) - inof('a')] == 2 ? bits_2_5[0] : bits_2_5[1];
    const char bit_5_in = bit_2_in == bits_2_5[0] ? bits_2_5[1] : bits_2_5[0];
    result[inof(bit_2_in) - inof('a')] = 2;
    result[inof(bit_5_in) - inof('a')] = 5;

    const auto bits_1_3 = outside_intersection(bits_2_5, gbl.at(4)[0]);
    const auto fs_5 = gather_freqs(join("", gbl.at(5)));
    const char bit_1_in =
        fs_5[inof(bits_1_3[0]) - inof('a')] == 1 ? bits_1_3[0] : bits_1_3[1];
    const char bit_3_in = bit_1_in == bits_1_3[0] ? bits_1_3[1] : bits_1_3[0];
    result[inof(bit_1_in) - inof('a')] = 1;
    result[inof(bit_3_in) - inof('a')] = 3;

    const string known{bit_0_in, bit_1_in, bit_2_in, bit_3_in, bit_5_in};
    const auto bits_4_6 = outside_intersection(known, "abcdefg");
    const char bit_4_in =
        fs_6[inof(bits_4_6[0]) - inof('a')] == 2 ? bits_4_6[0] : bits_4_6[1];
    const char bit_6_in = bit_4_in == bits_4_6[0] ? bits_4_6[1] : bits_4_6[0];
    result[inof(bit_4_in) - inof('a')] = 4;
    result[inof(bit_6_in) - inof('a')] = 6;

    return result;
}

int main() {
    int ans{};

    for (string line; getline(cin, line);) {
        const auto parts = split(" \\| ", line);
        const auto ivs = split(" ", parts[0]);
        const auto ovs = split(" ", parts[1]);

        const auto m = deduce_mapping(ivs);
        vector<int> xs(sz(ovs), -1);
        transform(cbegin(ovs), cend(ovs), begin(xs), [&](const auto &code) {
            return read_display(decode(m, code));
        });

        ans += number<int>(xs);
    }

    cout << ans << '\n';
    return 0;
}
