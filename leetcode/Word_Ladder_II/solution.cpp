#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;
using vi = vector<int>;
using vvi = vector<vi>;
using Graph = unordered_multimap<int, int>;

template <typename T> int index_of(const vector<T> &xs, const T &x) {
    const auto it = find(xs.cbegin(), xs.cend(), x);
    return it == xs.cend() ? -1 : distance(xs.cbegin(), it);
}

bool are_adjacent(const string &x, const string &y) {
    assert(x.size() == y.size());
    const int sz = x.size();
    int different = 0;
    for (int i = 0; i != sz; ++i) {
        if (x[i] != y[i]) {
            ++different;
            if (different > 1) return false;
        }
    }
    return different == 1;
}

Graph build_graph(const vs &dict) {
    const int sz = dict.size();
    Graph ans;
    for (int i = 0; i < sz - 1; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            if (are_adjacent(dict[i], dict[j])) {
                ans.emplace(i, j);
                ans.emplace(j, i);
            }
        }
    }
    return ans;
}

vs path_of_words(const vs &dict, const vi &indices) {
    vs ans;

    transform(indices.cbegin(), indices.cend(), back_inserter(ans),
              [&dict](const int i) { return dict[i]; });

    return ans;
}

vvs paths_of_words(const vs &dict, const vvi &xss) {
    vvs ans(xss.size());
    const auto map = [&dict](const vi &xs) { return path_of_words(dict, xs); };
    transform(xss.cbegin(), xss.cend(), ans.begin(), map);
    return ans;
}

template <typename T> vector<T> append(vector<T> xs, const T &x) {
    xs.push_back(x);
    return xs;
}

vvs all_paths(const vs &dict, const int s, const int t) {
    const auto g = build_graph(dict);

    int optimal_path_length = INT_MAX;
    queue<vi> q;
    q.push(vi{s});

    vvi xss;

    bool done = false;
    while (!q.empty()) {
        unordered_set<int> discovered;
        const int level_size = q.size();

        for (int i = 0; i != level_size; ++i) {
            const vi path = q.front();
            q.pop();

            for (auto it = path.crbegin(); it != path.crend(); ++it) {
                if (discovered.count(*it)) break;
                discovered.insert(*it);
            }

            assert(!path.empty());
            const int u = path.back();
            const int incremented_path_length = path.size() + 1;
            if (incremented_path_length > optimal_path_length) {
                done = true;
                break;
            }

            const auto [first, last] = g.equal_range(u);
            for (auto it = first; it != last; ++it) {
                const int v = it->second;
                if (discovered.count(v)) continue;

                if (v == t) {
                    optimal_path_length =
                        min(optimal_path_length, incremented_path_length);
                    xss.emplace_back(append(path, v));
                } else {
                    q.push(append(path, v));
                }
            }
        }
        if (done) break;
        discovered.clear();
    }

    return paths_of_words(dict, xss);
}

struct Solution final {
    vvs findLadders(const string &s, const string &t, vs dict) const {
        const int t_idx = index_of(dict, t);
        if (t_idx == -1) return {};
        dict.push_back(s);
        return all_paths(dict, dict.size() - 1, t_idx);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const vs dict{"hot","dot","dog","lot","log","cog"};
        auto actual = Solution{}.findLadders("hit", "cog", dict);
        sort(actual.begin(), actual.end());
        const vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const vs dict{"hot","dot","dog","lot","log"};
        const auto actual = Solution{}.findLadders("hit", "cog", dict);
        const vvs expected{};
        EXPECT(actual == expected);
    },
    CASE("Test case 18") {
        const vs dict{"hot","cog","dot","dog","hit","lot","log"};
        auto actual = Solution{}.findLadders("hit","cog", dict);
        sort(actual.begin(), actual.end());
        vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        sort(expected.begin(), expected.end());
        EXPECT(actual == expected);
    },
    CASE("Test case 22") {
        const vs dict{"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes",
                      "ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit",
                      "rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut",
                      "sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu",
                      "ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew",
                      "ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan",
                      "map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi",
                      "sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib",
                      "mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum",
                      "pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag",
                      "hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop",
                      "but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod",
                      "hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat",
                      "fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap",
                      "can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey",
                      "bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao",
                      "mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat",
                      "sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo",
                      "hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit",
                      "maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed",
                      "vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew",
                      "zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen",
                      "oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop",
                      "haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin",
                      "mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun",
                      "try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas",
                      "zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue",
                      "dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix",
                      "cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup",
                      "jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig",
                      "fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant",
                      "net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot",
                      "del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah",
                      "hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big",
                      "ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met",
                      "hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid",
                      "god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her",
                      "nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid",
                      "mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug",
                      "pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};
        auto actual = Solution{}.findLadders("cet","ism", dict);
        sort(actual.begin(), actual.end());
        vvs expected{
                     {"cet","get","gee","gte","ate","ats","its","ito","ibo","ibm","ism"},
                     {"cet","cat","can","ian","inn","ins","its","ito","ibo","ibm","ism"},
                     {"cet","cot","con","ion","inn","ins","its","ito","ibo","ibm","ism"}};
        sort(expected.begin(), expected.end());
        EXPECT(actual == expected);
    },
    CASE("Test case 26") {
        const vs dict{"ted","tex","red","tax","tad","den","rex","pee"};
        auto actual = Solution{}.findLadders("red", "tax", dict);
        sort(actual.begin(), actual.end());
        vvs expected{{"red","ted","tad","tax"},{"red","ted","tex","tax"},{"red","rex","tex","tax"}};
        sort(expected.begin(), expected.end());
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
