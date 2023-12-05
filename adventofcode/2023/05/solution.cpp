#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

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

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> parse_ints(const string &src) {
    const auto tokens = split(" ", src);
    vector<ll> result(sz(tokens));
    ranges::transform(tokens, begin(result),
                      [](const string &s) { return stoll(s); });
    return result;
}

pair<vector<pll>, vector<pll>> read_and_parse_range_lines() {
    vector<pll> a;
    vector<pll> b;

    for (string line; getline(cin, line) && !empty(line);) {
        const auto xs = parse_ints(line);
        assert(sz(xs) == 3);

        a.emplace_back(xs[0], xs[0] + xs[2] - 1);
        b.emplace_back(xs[1], xs[1] + xs[2] - 1);
    }

    return {a, b};
}

optional<int> index_of_containing_range(const vector<pll> &ranges, const ll x) {
    for (int i = 0; i < sz(ranges); ++i) {
        const auto [l, r] = ranges[i];
        if (l <= x && x <= r) return i;
    }
    return nullopt;
}

ll map_value(const vector<pll> &dst_ranges, const vector<pll> &src_ranges,
             const ll x) {
    const auto i = index_of_containing_range(src_ranges, x);
    if (!i) return x;

    const auto a0 = src_ranges[*i].first;
    const auto d = x - a0;

    const auto a1 = dst_ranges[*i].first;
    return a1 + d;
}

int main() {
    string line;
    getline(cin, line);
    const vector<ll> seeds = parse_ints(line.substr(sz(string{"seeds: "})));

    getline(cin, line);
    getline(cin, line);
    assert(line == "seed-to-soil map:");
    const auto [ss_seed_ranges, ss_soil_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "soil-to-fertilizer map:");
    const auto [sf_soil_ranges, sf_fert_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "fertilizer-to-water map:");
    const auto [fw_fert_ranges, fw_wat_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "water-to-light map:");
    const auto [wl_wat_ranges, wl_light_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "light-to-temperature map:");
    const auto [lt_light_ranges, lt_temp_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "temperature-to-humidity map:");
    const auto [th_temp_ranges, th_hum_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "humidity-to-location map:");
    const auto [hl_hum_ranges, hl_loc_ranges] = read_and_parse_range_lines();

    ll result = LONG_LONG_MAX;
    for (const auto seed : seeds) {
        const auto soil = map_value(ss_seed_ranges, ss_soil_ranges, seed);
        const auto fert = map_value(sf_soil_ranges, sf_fert_ranges, soil);
        const auto wat = map_value(fw_fert_ranges, fw_wat_ranges, fert);
        const auto light = map_value(wl_wat_ranges, wl_light_ranges, wat);
        const auto temp = map_value(lt_light_ranges, lt_temp_ranges, light);
        const auto hum = map_value(th_temp_ranges, th_hum_ranges, temp);
        const auto loc = map_value(hl_hum_ranges, hl_loc_ranges, hum);
        cerr << "seed: " << seed << " soil:" << soil << " fert:" << fert
             << " wat:" << wat << " light:" << light << " temp:" << temp
             << " hum:" << hum << " loc:" << loc << endl;

        result = min(result, loc);
    }
    cout << result << '\n';
    return 0;
}
