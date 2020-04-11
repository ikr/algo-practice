#include <bits/stdc++.h>

using namespace std;

struct PosNegDice final {
	 vector<int> evaluateRoll(const int t, vector<int> &posi, vector<int> &nega) const {
         multiset<int> posi_ms(posi.cbegin(), posi.cend());
         unordered_multiset<int> nega_ms(nega.cbegin(), nega.cend());
         
         for (auto it = posi_ms.begin(); it != posi_ms.end();) {
             if (nega_ms.count(*it)) {
             	nega_ms.erase(nega_ms.find(*it));
                it = posi_ms.erase(it);
             } else ++it;
         }
         
         const bool success = !posi_ms.empty() && *posi_ms.cbegin() <= t;
         
         return {success ? 1 : 0, static_cast<int>(nega_ms.size())};
     }
};
