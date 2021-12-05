#include "../common.hpp"


TEST(asm_sub, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_sub(rregister(l), rregister(r), o);
}

// Macro call structure:
// name,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed] [right size] [right trimmed]
// l/r/e - left/right/expected
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_SUB(n, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm_sub, n)                                                               \
    {                                                                              \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                              \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                              \
        AP_REGISTER(o, 4, 0, false);                                               \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                              \
        asm_sub(rregister(l), rregister(r), o);                                    \
        AP_ASSERT_REG(o, e);                                                       \
    }

AP_TEST_SUB(otzt,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED);

AP_TEST_SUB(otot,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);

AP_TEST_SUB(otou,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED);

AP_TEST_SUB(htzt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(huzt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(htot,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS1);

AP_TEST_SUB(htou,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(huot,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_SUB(huou,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(htht,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(hthu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(huhu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_SUB(ftzt,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(fuzt,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(ftot,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLB, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(ftou,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(fuot,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WCHESS1);

AP_TEST_SUB(fuou,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(ftht,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            4, AP_WFILLED, AP_WFILLED, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fthu,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLB, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            4, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WONLYLB);

AP_TEST_SUB(fuht,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fuhu,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WZEROED);

AP_TEST_SUB(ftft,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WFILLED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(ftfu,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WFILLED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fufu,
            4, AP_WZEROED, AP_WONLYLB, AP_WZEROED, AP_WFILLED,
            4, AP_WZEROED, AP_WZEROED, AP_WONLYLB, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);
