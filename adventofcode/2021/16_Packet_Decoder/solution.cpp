#include <bits/stdc++.h>
using namespace std;

using iter = string::const_iterator;
using ll = long long;

enum class Opcode {
    SUM = 0,
    PROD = 1,
    MIN = 2,
    MAX = 3,
    VAL = 4,
    GT = 5,
    LT = 6,
    EQ = 7
};

struct Packet final {
    int version;
    Opcode code;
    ll value;
    vector<Packet> sub;
};

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

pair<ll, iter> read_value(const iter last, iter i) {
    string xs;
    for (; i != last;) {
        const auto [x, keep_reading, i_] = read_value_chunk(i);
        i = i_;

        xs += bitset<4>(static_cast<unsigned long>(x)).to_string();

        if (!keep_reading) break;
    }

    return {stoll(xs, nullptr, 2), i};
}

vector<Packet> read_packets(const iter last, iter i);

pair<Packet, iter> read_packet(const iter last, iter i) {
    assert(i != last);

    const auto version = read_N<3>(i);
    i += 3;

    const auto type_id = read_N<3>(i);
    i += 3;

    if (type_id == inof(Opcode::VAL)) {
        const auto [value, it_] = read_value(last, i);
        i = it_;
        return {Packet{version, Opcode::VAL, value, {}}, i};
    } else { // it's an operator packet
        const auto length_type_id = read_N<1>(i);
        ++i;

        if (length_type_id == TOTAL_LENGTH_LTID) {
            const auto l = read_N<15>(i);
            i += 15;

            const auto xs = string(i, i + l);
            i += l;

            return {Packet{version, static_cast<Opcode>(type_id), 0,
                           read_packets(cend(xs), cbegin(xs))},
                    i};
        } else {
            assert(length_type_id == CHUNKS_NUM_LTID);
            const auto n = read_N<11>(i);
            i += 11;

            vector<Packet> ps;
            for (int j = 0; j < n; ++j) {
                const auto [p, i_] = read_packet(last, i);
                i = i_;
                ps.push_back(p);
            }
            return {Packet{version, static_cast<Opcode>(type_id), 0, ps}, i};
        }
    }
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

static constexpr ll INF = 1e18;

ll evaluate(const Packet &p) {
    switch (p.code) {
    case Opcode::SUM:
        return accumulate(
            cbegin(p.sub), cend(p.sub), 0LL,
            [](const ll agg, const Packet &pp) { return agg + evaluate(pp); });
    case Opcode::PROD:
        return accumulate(
            cbegin(p.sub), cend(p.sub), 1LL,
            [](const ll agg, const Packet &pp) { return agg * evaluate(pp); });
    case Opcode::MIN:
        assert(!p.sub.empty());
        return accumulate(cbegin(p.sub), cend(p.sub), INF,
                          [](const ll agg, const Packet &pp) {
                              return min(agg, evaluate(pp));
                          });
    case Opcode::MAX:
        assert(!p.sub.empty());
        return accumulate(cbegin(p.sub), cend(p.sub), -INF,
                          [](const ll agg, const Packet &pp) {
                              return max(agg, evaluate(pp));
                          });
    case Opcode::VAL:
        return p.value;
    case Opcode::GT:
        assert(sz(p.sub) == 2);
        return evaluate(p.sub[0]) > evaluate(p.sub[1]) ? 1 : 0;
    case Opcode::LT:
        assert(sz(p.sub) == 2);
        return evaluate(p.sub[0]) < evaluate(p.sub[1]) ? 1 : 0;
    case Opcode::EQ:
        assert(sz(p.sub) == 2);
        return evaluate(p.sub[0]) == evaluate(p.sub[1]) ? 1 : 0;
    default:
        cerr << "oc:" << inof(p.code) << endl;
        assert(false && "Impossible opcode");
        return -1;
    }
}

int main() {
    string src;
    cin >> src;

    const auto bits = hex_to_bin(src);

    const auto ps = read_packets(cend(bits), cbegin(bits));
    assert(sz(ps) == 1);
    cout << evaluate(ps[0]) << '\n';
    return 0;
}
