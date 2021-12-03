#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_twos)
{
    AP_REGISTER(i, 4, 0, false);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_twos(rregister(i), o);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(asm, tu_twos_zt)
{
    AP_REGISTER(i, 4, 0, false);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_ot)
{
    AP_REGISTER(i, 4, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_ht)
{
    AP_REGISTER(i, 4, 2, false, AP_WONLYLB, AP_WONLYLB);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WFILLED, AP_WMISSLB, AP_WFILLED, AP_WFILLED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_ft)
{
    AP_REGISTER(i, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WONLYLB, AP_WZEROED, AP_WZEROED, AP_WZEROED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_ou)
{
    AP_REGISTER(i, 4, 4, false, AP_WONLYLB, AP_WZEROED, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_hu)
{
    AP_REGISTER(i, 4, 4, false, AP_WONLYLB, AP_WONLYLB, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WFILLED, AP_WMISSLB, AP_WFILLED, AP_WFILLED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_twos_fu)
{
    AP_REGISTER(i, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WONLYLB, AP_WZEROED, AP_WFILLED, AP_WFILLED);
    asm_twos(rregister(i), o);
    AP_ASSERT_REG(o, e);
}
