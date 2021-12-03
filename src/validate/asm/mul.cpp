#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_mul)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_mul(rregister(l), rregister(r), o);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

#define AP_TEST_MUL(p, ecarry, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm, tu_mul_##p)                                                                  \
    {                                                                                      \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                      \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                                      \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                                      \
        AP_REGISTER(o, 4, 0, false);                                                       \
        dword_t c = asm_mul(rregister(l), rregister(r), o);                                \
        AP_ASSERT_REG(o, e);                                                               \
        ASSERT_EQ(c, ecarry);                                                              \
    }

// Macro call structure:
// prefix, expected carry
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// l/r/e - left/right/expected
// s - size
// x4 - the most significant word
// x1 - the least significant word

#define AP_WMPLIER word_t(AP_WONLYLW + 1)

AP_TEST_MUL(oott, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(ooc, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WMPLIER,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WZEROED);

AP_TEST_MUL(hott, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(hoc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            3, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW, AP_WZEROED);

AP_TEST_MUL(hhtt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(hhc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYLW, AP_WFILLED, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(fott, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(foc, 0,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WONLYHW);

AP_TEST_MUL(fow, AP_WONLYLW,
            4, AP_WONLYHW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WONLYHW);

AP_TEST_MUL(fhtt, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYHW, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(fhc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WONLYHW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(fhw, AP_WONLYLW,
            4, AP_WONLYLW, AP_WONLYHW, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WMPLIER, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(fftt, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);

AP_TEST_MUL(ffc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WONLYHW, AP_WFILLED, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(ffw, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYLW, AP_WONLYHW, AP_WZEROED,
            4, AP_WMPLIER, AP_WZEROED, AP_WZEROED, AP_WMPLIER,
            4, AP_WZEROED, AP_WFILLED, AP_WZEROED, AP_WZEROED);
