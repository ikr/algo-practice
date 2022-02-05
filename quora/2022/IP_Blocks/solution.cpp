#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

string octet_of(const ull base, const int i) {
    const auto shift = 8 * (3 - i);
    const auto mask = 255ULL << shift;
    return to_string(inof((base & mask) >> shift));
}

string format_ip(const pair<int, ull> &ip) {
    const auto [mask_bits, base] = ip;
    return octet_of(base, 0) + "." + octet_of(base, 1) + "." +
           octet_of(base, 2) + "." + octet_of(base, 3) + "/" +
           to_string(mask_bits);
}

pair<int, ull> parse_ip(const string &src) {
    const auto parts = split("/", src);
    assert(sz(parts) == 2);

    const auto base = parts[0];
    const auto mask_bits = stoi(parts[1]);

    const auto octets = split("\\.", base);
    assert(sz(octets) == 4);

    const auto o0 = stoull(octets[0]) << 24;
    const auto o1 = stoull(octets[1]) << 16;
    const auto o2 = stoull(octets[2]) << 8;
    const auto o3 = stoull(octets[3]);

    return {mask_bits, o0 | o1 | o2 | o3};
}

string as_prefix(const pair<int, ull> &ip) {
    const auto [mask_bits, base] = ip;
    if (mask_bits == 0) return "";
    const bitset<64> bits(base);

    string result(mask_bits, ' ');
    for (int i = 0; i < mask_bits; ++i) {
        result[i] = bits[31 - i] ? '1' : '0';
    }
    return result;
}

pair<int, ull> as_ip(const string &prefix) {
    const auto suffix =
        sz(prefix) == 32 ? string{""} : string(32 - sz(prefix), '0');
    const bitset<64> bits(string(32, '0') + prefix + suffix);
    return {sz(prefix), bits.to_ullong()};
}

string flip_last(string xs) {
    if (xs.back() == '0') {
        xs.back() = '1';
    } else {
        assert(xs.back() == '1');
        xs.back() = '0';
    }
    return xs;
}

vector<pair<int, ull>> simplify(const vector<pair<int, ull>> &ips) {
    set<string> prefs;

    for (auto &ip : ips) {
        const auto p = as_prefix(ip);
        if (p.empty()) return {parse_ip("0.0.0.0/0")};

        bool covered = false;
        for (int l = 1; l <= sz(p); ++l) {
            const auto p_ = p.substr(0, l);
            if (prefs.count(p_)) {
                covered = true;
                break;
            }
        }
        if (covered) continue;

        for (auto p_ = p;;) {
            const auto flipped = flip_last(p_);
            const auto it = prefs.find(flipped);
            if (it != cend(prefs)) {
                prefs.erase(it);
                const auto shorter = p_.substr(0, sz(p_) - 1);
                if (shorter.empty()) return {parse_ip("0.0.0.0/0")};
                p_ = shorter;
            } else {
                prefs.insert(p_);
                break;
            }
        }
    }

    vector<pair<int, ull>> result(sz(prefs));
    transform(cbegin(prefs), cend(prefs), begin(result), as_ip);
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<pair<int, ull>> ips;
    ips.reserve(n);

    for (int i = 1; i <= n; ++i) {
        string line;
        cin >> line;
        ips.push_back(parse_ip(line));
    }
    sort(begin(ips), end(ips));

    for (const auto &ip : simplify(ips)) {
        cout << format_ip(ip) << '\n';
    }
    return 0;
}
