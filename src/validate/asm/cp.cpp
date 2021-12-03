#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_cp)
{
    AP_REGISTER(i, 1, 1, false, 1);
    AP_REGISTER(o, 1, 1, false, 1);
    asm_cp(rregister(i), o);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(asm, tu_cp_zt)
{
    AP_REGISTER(i, 4, 0, false, 1);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 0, false, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_ot)
{
    AP_REGISTER(i, 4, 1, false, 1);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 1, false, 1);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_ht)
{
    AP_REGISTER(i, 4, 2, false, 1, 2);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 2, false, 1, 2);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_ft)
{
    AP_REGISTER(i, 4, 4, false, 1, 2, 3, 4);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, 1, 2, 3, 4);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_uo)
{
    AP_REGISTER(i, 4, 1, false, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 1, false, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_hu)
{
    AP_REGISTER(i, 4, 2, false, 1, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 2, false, 1, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm, tu_cp_fu)
{
    AP_REGISTER(i, 4, 4, false, 1, 2, 0, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, 1, 2, 0, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}
