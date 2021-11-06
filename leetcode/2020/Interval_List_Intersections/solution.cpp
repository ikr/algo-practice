using vi = vector<int>;
using vvi = vector<vi>;
using tiiii = tuple<int, int, int, int>;

vi intersect(const vi &u, const vi &v) {
    const auto [a, b, c, d] = tiiii{u[0], u[1], v[0], v[1]};
    if (b < c || d < a) return {};
    
    vi xs{a, b, c, d};
    sort(xs.begin(), xs.end());
    return {xs[1], xs[2]};
}

struct Solution final {
    vvi intervalIntersection(const vvi &iis, const vvi &jjs) {
        vvi ans;
        
        for (auto it = iis.cbegin(), jt = jjs.cbegin(); it != iis.cend() && jt != jjs.cend();) {
            const vi x = intersect(*it, *jt);
            if (!x.empty()) ans.push_back(x);
            
            const auto [a, b, c, d] = tiiii{(*it)[0], (*it)[1], (*jt)[0], (*jt)[1]};
            
            if (b <= c) ++it;
            else if (d <= a) ++jt;
            else if (d <= b) ++jt; 
            else if (b < d) ++it;
        }
        
        return ans;
    }
};
