struct Solution final {
    int findTheDistanceValue(vector<int> &xs, vector<int> &ys,
                             const int d) const {
        int ans = 0;

        for (const int x : xs) {
            bool ok = true;

            for (const int y : ys) {
                if (abs(x - y) <= d) {
                    ok = false;
                    break;
                }
            }

            if (ok) ++ans;
        }

        return ans;
    }
};
