#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

using iter = string::const_iterator;

struct Packet final {
    int version;
};

static constexpr int LITERAL_TID = 4;
static constexpr int TOTAL_LENGTH_LTID = 0;
static constexpr int CHUNKS_NUM_LTID = 1;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <size_t N> int read_N(const iter i) {
    return inof(bitset<N>(string(i, i + N)).to_ulong());
}

tuple<int, bool, iter> read_value_chunk(iter i) {
    const auto src = read_N<5>(i);
    i += 5;

    const bool keep_reading = (1 << 4) & src;
    const int x = ((1 << 4) - 1) & src;

    return tuple{x, keep_reading, i};
}

pair<vector<int>, iter> read_value(const iter last, iter i) {
    vector<int> xs;
    for (; i != last;) {
        const auto [x, keep_reading, i_] = read_value_chunk(i);
        i = i_;
        xs.push_back(x);

        if (!keep_reading) {
            while (i != last && *i == '0') ++i;
            break;
        }
    }

    return {xs, i};
}

optional<pair<Packet, iter>> read_packet(const iter last, iter i) {
    if (i == last) return nullopt;

    const auto version = read_N<3>(i);
    i += 3;

    const auto type_id = read_N<3>(i);
    i += 3;

    if (type_id == LITERAL_TID) {
        const auto [xs, it_] = read_value(last, i);
        i = it_;
    } else { // it's an operator packet
        const auto length_type_id = read_N<1>(i);
        ++i;

        if (length_type_id == TOTAL_LENGTH_LTID) {
            const auto l = read_N<15>(i);
            i += 15;

            const auto xs = string(i, i + l);
            i += l;
            read_value(cend(xs), cbegin(xs));
            while (i != last && *i == '0') ++i;
        } else {
            assert(length_type_id == CHUNKS_NUM_LTID);
            const auto n = read_N<11>(i);
            i += 11;

            const auto [xs, it_] = read_value(last, i);
            i = it_;
            assert(sz(xs) == n);
        }
    }

    return pair{Packet{version}, i};
}

string hex_to_bin(const string &xs) {
    string result;
    for (const auto x : xs) {
        result +=
            bitset<4>(static_cast<unsigned long>(stoi(string{x}, nullptr, 16)))
                .to_string();
    }
    return result;
}

int main() {
    string src;
    cin >> src;

    const auto bits = hex_to_bin(src);
    cerr << bits << endl;

    for (auto i = cbegin(bits);;) {
        const auto res = read_packet(cend(bits), i);
        if (!res) break;

        const auto [p, i_] = *res;
        i = i_;
    }

    return 0;
}
