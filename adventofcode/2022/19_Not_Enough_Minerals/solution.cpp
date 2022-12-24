#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using Resources = array<int, 4>;
using Robots = array<int, 4>;
using ResId = int;

static constexpr int INF = 100'000'000;
static constexpr ResId ORE = 0;
static constexpr ResId CLAY = 1;
static constexpr ResId OBSIDIAN = 2;
static constexpr ResId GEODE = 3;
static constexpr int T = 24;

struct RobotCosts final {
    int ore_ore;
    int clay_ore;
    pii obsidian_ore_clay;
    pii geode_ore_obsidian;

    optional<Resources> buy_robot(const ResId id, Resources res) const {
        switch (id) {
        case ORE:
            if (res[ORE] >= ore_ore) {
                res[ORE] -= ore_ore;
                return res;
            }
            break;
        case CLAY:
            if (res[ORE] >= clay_ore) {
                res[ORE] -= clay_ore;
                return res;
            }
            break;
        case OBSIDIAN:
            if (res[ORE] >= obsidian_ore_clay.first &&
                res[CLAY] >= obsidian_ore_clay.second) {
                res[ORE] -= obsidian_ore_clay.first;
                res[CLAY] -= obsidian_ore_clay.second;
                return res;
            }
            break;
        case GEODE:
            if (res[ORE] >= geode_ore_obsidian.first &&
                res[OBSIDIAN] >= geode_ore_obsidian.second) {
                res[ORE] -= geode_ore_obsidian.first;
                res[OBSIDIAN] -= geode_ore_obsidian.second;
                return res;
            }
            break;
        default:
            assert(false && "Invalid resource id");
            return res;
        }

        return nullopt;
    }

    int max_required(const ResId id) const {
        switch (id) {
        case ORE:
            return max({ore_ore, clay_ore, obsidian_ore_clay.first,
                        geode_ore_obsidian.first});
        case CLAY:
            return obsidian_ore_clay.second;
        case OBSIDIAN:
            return geode_ore_obsidian.second;
        case GEODE:
            return INF;
        default:
            assert(false && "Invalid resource id");
            return 0;
        }
    }
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

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
    int geodes_max{};

    const auto recur = [&](const auto self, const int t, const Resources &res,
                           const Robots &rob) -> void {
        if (!t) {
            geodes_max = max(geodes_max, res[GEODE]);
            return;
        };

        self(self, t - 1, res + rob, rob);

        for (const auto id : {ORE, CLAY, OBSIDIAN, GEODE}) {
            if (id != GEODE) {
                const auto hi = costs.max_required(id);
                if (rob[id] >= hi || res[id] + t - 1 > hi * (t - 1)) {
                    continue;
                }
            }

            auto res_ = costs.buy_robot(id, res);
            if (!res_) continue;
            *res_ = *res_ + rob;

            auto rob_ = rob;
            ++rob_[id];
            self(self, t - 1, *res_, rob_);
        }
    };

    recur(recur, T, {0, 0, 0}, {1, 0, 0, 0});
    return geodes_max;
}

int first_3_geodes_max_product(const vector<RobotCosts> &blueprints) {
    int result = 1;
    for (int i = 0; i < min(sz(blueprints), 3); ++i) {
        const auto geodes = max_geodes_gathered(blueprints[i]);
        cerr << "Blueprint " << (i + 1) << " — " << geodes << " geodes" << endl;
        result *= geodes;
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
    }

    cout << first_3_geodes_max_product(blueprints) << '\n';
    return 0;
}
