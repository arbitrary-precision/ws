#include "../common.hpp"


TEST(asm_lsh, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_lsh(rregister(l), 1, o);
}

// Macro call structure:
// name,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed/carry/wrapping]. carry/wrapping implies trimmed.
// l/r/e - left/right/expected
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_LSH(n, ls, l4, l3, l2, l1, es, e4, e3, e2, e1) \
    TEST(asm_lsh_, n)                                          \
    {                                                          \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);          \
        AP_REGISTER(o, 4, 0, false);                           \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);          \
        asm_lsh(rregister(l), word_traits::bits / 2, o);       \
        AP_ASSERT_REG(o, e);                                   \
    }

AP_TEST_LSH(ot,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_LSH(ou,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_LSH(oc,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WZEROED);

AP_TEST_LSH(ht,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_LSH(hu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WONLYHW);

AP_TEST_LSH(hc,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WONLYHW,
            3, AP_WHEPROT, AP_WONLYLW, AP_WFILLED, AP_WZEROED);

AP_TEST_LSH(ft,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_LSH(fu,
            4, AP_WZEROED, AP_WZEROED, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_LSH(fc,
            4, AP_WONLYLW, AP_WONLYLW, AP_WFILLED, AP_WONLYHW,
            4, AP_WONLYHW, AP_WFILLED, AP_WFILLED, AP_WZEROED);

AP_TEST_LSH(fw,
            4, AP_WONLYHW, AP_WONLYLW, AP_WFILLED, AP_WONLYHW,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WZEROED);
