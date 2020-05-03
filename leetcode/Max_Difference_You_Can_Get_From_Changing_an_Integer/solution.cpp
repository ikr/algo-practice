vector<int> digits(int x) {
    vector<int> ans;
    
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
}

int num(const vector<int> &digits) {
    int ans = 0;
    
    for (const int d : digits) {
        ans *= 10;
        ans += d;
    }
    
    return ans;
}

void replace_ds(vector<int> &digits, const int x, const int y) {
    for (int &d : digits) {
        if (d == x) d = y;
    }
}

struct Solution final {
    int maxDiff(const int x) const {
        auto da = digits(x);
        auto db = da;
        
        const auto ita = find_if(da.cbegin(), da.cend(), [](const int d) { return d != 9; });
        
        if (ita != da.cend()) {
            replace_ds(da, *ita, 9);
        }
        
        const auto itb = (db[0] == 1) ? 
            find_if(db.cbegin() + 1, db.cend(), [](const int d) { return d != 0 && d != 1; }) :
            db.cbegin();

        if (itb != db.cend()) {
            replace_ds(db, *itb, itb == db.cbegin() ? 1 : 0);
        }
        
        return num(da) - num(db);
    }
};
