using vi = vector<int>;
using vvi = vector<vi>;

constexpr int measure(const vi &xy) {
    return xy[0] * xy[0] + xy[1] * xy[1];
}

struct Solution final {
    vvi kClosest(vvi xys, const int k) const {
        nth_element(xys.begin(), xys.begin() + k, xys.end(), [](const vi &lhs, const vi &rhs) {
            return measure(lhs) < measure(rhs);
        });
        
        vvi ans(xys.begin(), xys.begin() + k);
        return ans;
    }
};
