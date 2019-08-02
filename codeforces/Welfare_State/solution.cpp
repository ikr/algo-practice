#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;
using BalPer = pair<ui_t, ui_t>;

enum class EventType { RECEIPT = 1, PAYOFF = 2 };

void handle_receipt(vector<ui_t> &balances_by_person,
                    set<BalPer> &persons_by_balance, const BalPer receipt) {
    const auto [new_balance, person] = receipt;
    const ui_t old_balance = balances_by_person[person];

    balances_by_person[person] = new_balance;

    persons_by_balance.erase(BalPer{old_balance, person});
    persons_by_balance.insert(receipt);
}

void handle_payoff(vector<ui_t> &balances_by_person,
                   set<BalPer> &persons_by_balance, const ui_t threshold) {
    vector<ui_t> persons_to_pay_off;
    transform(persons_by_balance.cbegin(),
              upper_bound(persons_by_balance.cbegin(),
                          persons_by_balance.cend(), BalPer{threshold, 0U}),
              back_inserter(persons_to_pay_off),
              [](const auto bp) { return bp.second; });

    for (const auto p : persons_to_pay_off) {
        handle_receipt(balances_by_person, persons_by_balance, {threshold, p});
    }
}

int main() {
    ui_t n;
    cin >> n;

    vector<ui_t> balances_by_person(n + 1, 0U);
    set<BalPer> persons_by_balance;

    for (ui_t i = 1; i <= n; ++i) {
        cin >> balances_by_person[i];
        persons_by_balance.insert(BalPer{balances_by_person[i], i});
    }

    ui_t events_count;
    cin >> events_count;

    for (ui_t i = 0; i != events_count; ++i) {
        ui_t event_type;
        cin >> event_type;

        if (event_type == static_cast<ui_t>(EventType::RECEIPT)) {
            ui_t person;
            ui_t new_balance;
            cin >> person >> new_balance;

            handle_receipt(balances_by_person, persons_by_balance,
                           {new_balance, person});
        } else {
            ui_t threshold;
            cin >> threshold;

            handle_payoff(balances_by_person, persons_by_balance, threshold);
        }
    }

    for (ui_t i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << balances_by_person[i];
    }
    cout << '\n';
}
