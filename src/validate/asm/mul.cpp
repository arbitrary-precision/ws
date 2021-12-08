#include "../common.hpp"

TEST(asm_mul, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_mul(rregister(l), rregister(r), o);
}

// Macro call structure:
// prefix, expected carry
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed/carry/wrapping] [right size] [right trimmed/carry/wrapping]. carry/wrapping implies trimmed.
// l/r/e - left/right/expected. Right is an out here, since its digits are used in computation.
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_MUL(n, ecarry, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm_mul, n)                                                                       \
    {                                                                                      \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                      \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                                      \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                                      \
        AP_REGISTER(o, 4, 0, false);                                                       \
        dword_t c = asm_mul(rregister(l), rregister(r), o);                                \
        AP_ASSERT_REG(o, e);                                                               \
        ASSERT_EQ(c, ecarry);                                                              \
    }

#define AP_WMPLIER word_t(AP_WONLYLW + 1)

AP_TEST_MUL(otot, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(ococ, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WMPLIER,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WZEROED);

AP_TEST_MUL(htot, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(hcoc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            3, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW, AP_WZEROED);

AP_TEST_MUL(htht, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(hchc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYLW, AP_WFILLED, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(ftot, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(fcoc, 0,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WONLYHW);

AP_TEST_MUL(fwow, AP_WONLYLW,
            4, AP_WONLYHW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WONLYHW);

AP_TEST_MUL(ftht, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYHW, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(fchc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYHW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(fwhw, AP_WONLYLW,
            4, AP_WONLYLW, AP_WONLYHW, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(ftft, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(fcfc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WONLYHW, AP_WFILLED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(fwfw, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WZEROED, AP_WFILLED, AP_WZEROED, AP_WZEROED);
