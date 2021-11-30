#include "../utils.hpp"
#include <ap/asm.hpp>
#include <gtest/gtest.h>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_div)
{
    REGISTER(left, 2, 2, false, 1, 1);
    REGISTER(right, 2, 2, false, 1, 1);
    REGISTER(quo, 2, 2, false, WORD5, WORD5);
    REGISTER(rem, 2, 2, false, WORD5, WORD5);
    asm_div(rregister(left), rregister(right), quo, rem);
}
