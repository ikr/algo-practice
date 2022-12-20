#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using Resources = array<int, 4>;
using Robots = array<int, 4>;

static constexpr int ORE = 0;
static constexpr int CLAY = 1;
static constexpr int OBSIDIAN = 2;
static constexpr int GEODE = 3;
static constexpr int T = 24;

struct RobotCosts final {
    int ore_ore;
    int clay_ore;
    pii obsidian_ore_clay;
    pii geode_ore_obsidian;

    optional<Resources> buy_ore_robot(Resources res) const {
        if (res[ORE] >= ore_ore) {
            res[ORE] -= ore_ore;
            return res;
        }
        return nullopt;
    }

    optional<Resources> buy_clay_robot(Resources res) const {
        if (res[ORE] >= clay_ore) {
            res[ORE] -= clay_ore;
            return res;
        }
        return nullopt;
    }

    optional<Resources> buy_obsidian_robot(Resources res) const {
        if (res[ORE] >= obsidian_ore_clay.first &&
            res[CLAY] >= obsidian_ore_clay.second) {
            res[ORE] -= obsidian_ore_clay.first;
            res[CLAY] -= obsidian_ore_clay.second;
            return res;
        }
        return nullopt;
    }

    optional<Resources> buy_geode_robot(Resources res) const {
        if (res[ORE] >= geode_ore_obsidian.first &&
            res[OBSIDIAN] >= geode_ore_obsidian.second) {
            res[ORE] -= geode_ore_obsidian.first;
            res[OBSIDIAN] -= geode_ore_obsidian.second;
            return res;
        }
        return nullopt;
    }
};

ostream &operator<<(ostream &os, const RobotCosts &cst) {
    os << '{' << "Ore-R: " << cst.ore_ore << "ore, Clay-R: " << cst.clay_ore
       << "ore, Obsidian-R: " << cst.obsidian_ore_clay.first << "ore "
       << cst.obsidian_ore_clay.second
       << "clay, Geode-R: " << cst.geode_ore_obsidian.first << "ore "
       << cst.geode_ore_obsidian.second << "obsidian}";
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> size_t combine_hashes(const T &xs) {
    size_t seed = xs.size();
    for (const auto i : xs) seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

size_t state_key(const int t, const Resources &res, const Robots &rob) {
    return combine_hashes(array<size_t, 3>{
        static_cast<size_t>(t), combine_hashes(res), combine_hashes(rob)});
}

template <typename T, size_t N>
constexpr array<T, N> operator+(array<T, N> a, const array<T, N> &b) {
    transform(cbegin(a), cend(a), cbegin(b), begin(a),
              [](const T x, const T y) { return x + y; });
    return a;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int max_geodes_gathered(const RobotCosts &costs) {
    unordered_map<size_t, int> memo;

    const auto recur = [&](const auto self, const int t, const Resources &res,
                           const Robots &rob) -> int {
        const auto key = state_key(t, res, rob);
        if (memo.contains(key)) return memo.at(key);
        return memo[key] = [&]() -> int {
            if (!t) return res[GEODE];

            const auto o_none = self(self, t - 1, res + rob, rob);

            const auto o_ore = [&]() -> int {
                auto mb_res = costs.buy_ore_robot(res);
                if (!mb_res) return INT_MIN;
                *mb_res = *mb_res + rob;

                auto rob_ = rob;
                ++rob_[ORE];
                return self(self, t - 1, *mb_res, rob_);
            }();

            const auto o_clay = [&]() -> int {
                auto mb_res = costs.buy_clay_robot(res);
                if (!mb_res) return INT_MIN;
                *mb_res = *mb_res + rob;

                auto rob_ = rob;
                ++rob_[CLAY];
                return self(self, t - 1, *mb_res, rob_);
            }();

            const auto o_obsidian = [&]() -> int {
                auto mb_res = costs.buy_obsidian_robot(res);
                if (!mb_res) return INT_MIN;
                *mb_res = *mb_res + rob;

                auto rob_ = rob;
                ++rob_[OBSIDIAN];
                return self(self, t - 1, *mb_res, rob_);
            }();

            const auto o_geode = [&]() -> int {
                auto mb_res = costs.buy_geode_robot(res);
                if (!mb_res) return INT_MIN;
                *mb_res = *mb_res + rob;

                auto rob_ = rob;
                ++rob_[GEODE];
                return self(self, t - 1, *mb_res, rob_);
            }();

            return max({o_none, o_ore, o_clay, o_obsidian, o_geode});
        }();
    };

    return recur(recur, T, {0, 0, 0, 0}, {1, 0, 0, 0});
}

int quality_level(const vector<RobotCosts> &blueprints) {
    int result{};
    for (int i = 0; i < sz(blueprints); ++i) {
        const auto geodes = max_geodes_gathered(blueprints[i]);
        cerr << "Blueprint " << (i + 1) << " — " << geodes << " geodes" << endl;
        result += (i + 1) * geodes;
    }
    return result;
}

int main() {
    const regex pattern{
        "^Blueprint [0-9]{1,2}: Each ore robot costs ([0-9]+) ore. Each clay "
        "robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and "
        "([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) "
        "obsidian.$"};

    vector<RobotCosts> blueprints;

    for (string line; getline(cin, line);) {
        smatch m;
        regex_match(line, m, pattern);
        const auto m_at = [&m](const int i) -> int { return stoi(m[i]); };

        blueprints.push_back(RobotCosts{m_at(1), m_at(2), pii{m_at(3), m_at(4)},
                                        pii{m_at(5), m_at(6)}});

        cerr << blueprints.back() << endl;
    }

    cout << quality_level(blueprints) << '\n';
    return 0;
}
