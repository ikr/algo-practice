using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using vi = vector<int>;
using vui = vector<int>;
using vll = vector<ll>;

static const ll M = 1e9 + 7;
static const ui MAX_HAT = 40;
static const ui MAX_PERSON = 9;
static const ui MAX_PERSON_COMBO = (1 << 10) - 1;

vui people_bits_by_hat(const vector<vi> &hats_by_person) {
    const ui sz = hats_by_person.size();
    assert(sz <= MAX_PERSON + 1U);
    vui ans(MAX_HAT + 1, 0U);
    
    for (ui i = 0U; i != sz; ++i) {
        for (const int h : hats_by_person[i]) ans[h] |= (1U << i);
    }
    
    return ans;
}

ll people_bits_popcount(const ui people_bits) {
    return bitset<MAX_PERSON + 1>(people_bits).count();
}

ll max_overall(vector<vll> xss) {
    ll ans = 0;
    
    for (const auto &xs : xss) {
        ans = max(ans, *max_element(xs.cbegin(), xs.cend()));
    }
    
    return ans;
}

struct Solution final {
    int numberWays(const vector<vi> &hats_by_person) const {
        const auto pbbh = people_bits_by_hat(hats_by_person);
        
        // answer [up to hat i] [with people bits combo j already assigned]
        vector<vll> dp(MAX_HAT + 1, vll(MAX_PERSON_COMBO + 1, 0));
        
        for (ui j = 1; j <= MAX_PERSON_COMBO; ++j) {
            dp[1][j] = people_bits_popcount(pbbh[1]);
        }
        
        for (ui i = 2; i <= MAX_HAT; ++i) {
            for (ui j = 1; j <= MAX_PERSON_COMBO; ++j) {
                dp[i][j] = 
            }
        }
        
        return max_overall(dp);
    }
};
