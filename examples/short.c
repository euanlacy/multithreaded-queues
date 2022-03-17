#include "../src/knuth_bendix.h"
#include "../src/lists.h"
#include "../src/brute_force.h"

int main() {
    RuleList* rules = RuleList_new(10);
    /* RuleList_push(rules, (Rule) {"aa",    "", 2, 0}); */
    /* RuleList_push(rules, (Rule) {"bbb",   "", 3, 0}); */
    /* RuleList_push(rules, (Rule) {"abba",  "bab", 4, 3}); */
    /* RuleList_push(rules, (Rule) {"baba",  "abb", 4, 3}); */
    /* RuleList_push(rules, (Rule) {"abab",  "bba"}); */
    /* RuleList_push(rules, (Rule) {"bbabb", "aba"}); */

    RuleList_push(rules, (Rule) {"aa",    "", 2, 0});
    RuleList_push(rules, (Rule) {"bbb",   "", 3, 0});
    RuleList_push(rules, (Rule) {"ababab",  "", 6, 0});

    RuleList* confluent = kbs_2(rules, brute_force);
    printf("%d\n", check_confluent(confluent));
    RuleList_print(confluent);
    printf("Num rules: %d\n", confluent->len);

    for (int i = 0; i < confluent->len; i++) {
        free(confluent->buf[i].left);
        free(confluent->buf[i].right);
    }

    RuleList_destroy(confluent);
    RuleList_destroy(rules);
}
