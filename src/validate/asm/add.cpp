#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_add)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_add(rregister(l), rregister(r), o);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

#define AP_TEST_ADD(p, ecarry, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm, tu_add_##p)                                                                  \
    {                                                                                      \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                      \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                                      \
        AP_REGISTER(o, 4, 0, false);                                                       \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                                      \
        dword_t c = asm_add(rregister(l), rregister(r), o);                                \
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
AP_TEST_ADD(zztt, 0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_ADD(oztt, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(ozut, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(oott, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(ootu, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(oout, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_ADD(oouu, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(ooc, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WZEROED);

AP_TEST_ADD(hztt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(hzut, 0,
            2, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(hott, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(hotu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(hout, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(houu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(hoc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            3, AP_WHEPROT, AP_WONLYLB, AP_WZEROED, AP_WMISSLB);

AP_TEST_ADD(hhtt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(hhtu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(hhut, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS1, AP_WFILLED);

AP_TEST_ADD(hhuu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(hhc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WONLYLB,
            3, AP_WHEPROT, AP_WONLYLB, AP_WFILLED, AP_WZEROED);

AP_TEST_ADD(fztt, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fzut, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fott, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS1);

AP_TEST_ADD(fotu, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fout, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fouu, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(foc, 0,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WONLYLB, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(fow, 1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(fhtt, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fhtu, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fhut, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fhuu, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fhc, 0,
            4, AP_WCHESS0, AP_WZEROED, AP_WONLYLB, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WZEROED,
            4, AP_WCHESS0, AP_WONLYLB, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(fhw, 1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(fftt, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fftu, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS0, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(ffut, 0,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS1, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(ffuu, 0,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(ffc, 0,
            4, AP_WZEROED, AP_WONLYLB, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WFILLED, AP_WCHESS1, AP_WCHESS1,
            4, AP_WONLYLB, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(ffw, 1,
            4, AP_WFILLED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WONLYLB, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
