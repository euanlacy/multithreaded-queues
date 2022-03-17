#include "../src/knuth_bendix.h"
#include "../src/lists.h"
#include "../src/brute_force.h"

int main() {
    RuleList* rules = RuleList_new(10);
    RuleList_push(rules, (Rule) {"aa",  ""});
    RuleList_push(rules, (Rule) {"BB",  "b"});
    RuleList_push(rules, (Rule) {"BaBaBaB",  "abababa"});
    RuleList_push(rules, (Rule) {"aBabaBabaBabaBab",  "BabaBabaBabaBaba"});
    RuleList_push(rules, (Rule) {"bB",  ""});
    RuleList_push(rules, (Rule) {"Bb",  ""});

    RuleList* confluent = kbs_2(rules, brute_force);
    printf("Num rules: %d\n", confluent->len);
}
