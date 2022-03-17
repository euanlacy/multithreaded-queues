from libsemigroups_pybind11 import KnuthBendix

kb = KnuthBendix()
kb.set_alphabet("abB")
kb.set_identity("")
kb.set_inverses("aBb")

kb.add_rule("aa", "")
kb.add_rule("BB", "b")
kb.add_rule("BaBaBaB",  "abababa")
kb.add_rule("aBabaBabaBabaBab",  "BabaBabaBabaBaba")
kb.run()

print(kb.number_of_active_rules())
