using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using vui = vector<int>;
using vll = vector<ll>;

static const ll M = 1e9 + 7;
static const ui MAX_HAT = 40;
static const ui MAX_PERSON = 4;
static const ui MAX_PEOPLE_BITS = (1 << 5) - 1;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

vui people_bits_by_hat(const vector<vi> &hats_by_person) {
    const ui sz = hats_by_person.size();
    assert(sz <= MAX_PERSON + 1U);
    vui ans(MAX_HAT + 1, 0U);
    
    for (ui i = 0U; i != sz; ++i) {
        for (const int h : hats_by_person[i]) ans[h] |= (1U << i);
    }
    
    return ans;
}

ui people_bits_compliment(const ui people_bits) {
    return ~people_bits & MAX_PEOPLE_BITS;
}

struct Solution final {
    int numberWays(const vector<vi> &hats_by_person) const {
        const auto pbbh = people_bits_by_hat(hats_by_person);
        
        // answer [up to hat i] [with people bits combo j allowed]
        vector<vll> dp(MAX_HAT + 1, vll(MAX_PEOPLE_BITS + 1, 1LL));
        
        for (ui i = 1; i <= MAX_HAT; ++i) {
            for (ui j = 1; j <= MAX_PEOPLE_BITS; ++j) {
                const ll own_count = __builtin_popcount(pbbh[i] & j);
                const ui compatible_combo = people_bits_compliment(pbbh[i] & j);
                const ll inherited_count = dp[i - 1][compatible_combo];
                
                dp[i][j] = (inherited_count * own_count) % M;
            }
        }
        
        for (const auto &row : dp) {
            cout << row << '\n';
        }
        
        return 0;
    }
};
