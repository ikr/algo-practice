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

constexpr optional<pll> intersection(const pll &ab, const pll &cd) {
    const auto [a, b] = ab;
    const auto [c, d] = cd;
    assert(a <= b);
    assert(c <= d);
    if (b < c || d < a) return nullopt;

    array xs{a, b, c, d};
    ranges::sort(xs);
    return pll{xs[1], xs[2]};
}

vector<pll> ab_without_cd(const pll &ab, const pll &cd) {
    const auto xy = intersection(ab, cd);
    assert(xy);
    if (*xy == ab) return {};
    const auto [x, y] = *xy;
    assert(x <= y);

    const auto [a, b] = ab;
    if (x == a) return {{y + 1, b}};
    if (y == b) return {{a, x - 1}};
    assert(a < x && y < b);
    return {{a, x - 1}, {y + 1, b}};
}

ll map_value(const pll &src_range, const pll &dst_range, const ll x) {
    const auto [a0, b0] = src_range;
    assert(a0 <= x && x <= b0);

    const auto d = x - a0;
    const auto a1 = dst_range.first;
    return a1 + d;
}

pll map_interval(const pll &src_range, const pll &dst_range, const pll &xy) {
    return {map_value(src_range, dst_range, xy.first),
            map_value(src_range, dst_range, xy.second)};
}

vector<pll> map_intervals(const vector<pll> &src_ranges,
                          const vector<pll> &dst_ranges, vector<pll> A) {
    assert(sz(src_ranges) == sz(dst_ranges));
    vector<pll> B;

    for (int i = 0; i < sz(src_ranges); ++i) {
        vector<pll> A_;

        for (const auto &ab : A) {
            const auto xy = intersection(ab, src_ranges[i]);
            if (xy) {
                B.push_back(map_interval(src_ranges[i], dst_ranges[i], *xy));
                const auto cuts = ab_without_cd(ab, *xy);
                A_.insert(cend(A_), cbegin(cuts), cend(cuts));
            } else {
                A_.push_back(ab);
            }
        }

        swap(A, A_);
    }

    B.insert(cend(B), cbegin(A), cend(A));
    return B;
}

int main() {
    string line;
    getline(cin, line);
    const vector<ll> seeds_src = parse_ints(line.substr(sz(string{"seeds: "})));
    assert(sz(seeds_src) % 2 == 0);

    vector<pll> intervals;
    for (int i = 0; i < sz(seeds_src); i += 2) {
        intervals.emplace_back(seeds_src[i],
                               seeds_src[i] + seeds_src[i + 1] - 1);
    }
    assert(sz(intervals) == sz(seeds_src) / 2);

    getline(cin, line);
    getline(cin, line);
    assert(line == "seed-to-soil map:");
    const auto [ss_soil_ranges, ss_seed_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "soil-to-fertilizer map:");
    const auto [sf_fert_ranges, sf_soil_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "fertilizer-to-water map:");
    const auto [fw_wat_ranges, fw_fert_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "water-to-light map:");
    const auto [wl_light_ranges, wl_wat_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "light-to-temperature map:");
    const auto [lt_temp_ranges, lt_light_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "temperature-to-humidity map:");
    const auto [th_hum_ranges, th_temp_ranges] = read_and_parse_range_lines();

    getline(cin, line);
    assert(line == "humidity-to-location map:");
    const auto [hl_loc_ranges, hl_hum_ranges] = read_and_parse_range_lines();

    const vector<pair<vector<pll>, vector<pll>>> stages{
        {ss_seed_ranges, ss_soil_ranges},  {sf_soil_ranges, sf_fert_ranges},
        {fw_fert_ranges, fw_wat_ranges},   {wl_wat_ranges, wl_light_ranges},
        {lt_light_ranges, lt_temp_ranges}, {th_temp_ranges, th_hum_ranges},
        {hl_hum_ranges, hl_loc_ranges}};

    ranges::sort(intervals);
    cerr << intervals << endl;

    for (const auto &[src_ranges, dst_ranges] : stages) {
        intervals = map_intervals(src_ranges, dst_ranges, intervals);
        ranges::sort(intervals);
        cerr << intervals << endl;
    }

    cout << intervals[0].first << endl;
    return 0;
}
