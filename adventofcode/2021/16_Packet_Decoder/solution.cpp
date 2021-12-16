#include <bits/stdc++.h>
using namespace std;

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

pair<string, iter> read_value(const iter last, iter i) {
    string xs;
    for (; i != last;) {
        const auto [x, keep_reading, i_] = read_value_chunk(i);
        i = i_;

        xs += bitset<4>(static_cast<unsigned long>(x)).to_string();

        if (!keep_reading) break;
    }

    cerr << "read_value:" << stoll(xs, nullptr, 2) << endl;
    return {xs, i};
}

vector<Packet> read_packets(const iter last, iter i);

static int ans{};

pair<Packet, iter> read_packet(const iter last, iter i) {
    assert(i != last);

    const auto version = read_N<3>(i);
    ans += version;
    cerr << "v:" << version << endl;
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

            read_packets(cend(xs), cbegin(xs));
        } else {
            assert(length_type_id == CHUNKS_NUM_LTID);
            const auto n = read_N<11>(i);
            i += 11;

            for (int j = 0; j < n; ++j) {
                const auto [p, i_] = read_packet(last, i);
                i = i_;
            }
        }
    }

    return pair{Packet{version}, i};
}

vector<Packet> read_packets(const iter last, iter i) {
    vector<Packet> result;

    for (; i != last;) {
        if (all_of(i, last, [](const char d) { return d == '0'; })) break;
        const auto [p, i_] = read_packet(last, i);
        result.push_back(p);
        i = i_;
    }

    return result;
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

    read_packets(cend(bits), cbegin(bits));
    cout << "ans:" << ans << '\n';
    return 0;
}
