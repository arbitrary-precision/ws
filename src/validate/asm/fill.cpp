#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_fill)
{
    AP_REGISTER(x, 1, 1, false, 0);
    asm_fill(x, AP_WCHESS1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(asm, tu_fill_z)
{
    AP_REGISTER(x, 4, 0, false, 0);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm, tu_fill_o)
{
    AP_REGISTER(x, 4, 1, false, 1);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm, tu_fill_h)
{
    AP_REGISTER(x, 4, 2, false, 1, 2);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm, tu_fill_f)
{
    AP_REGISTER(x, 4, 4, false, 1, 2, 3, 4);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}
