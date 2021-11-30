#include "../utils.hpp"
#include <ap/asm.hpp>
#include <gtest/gtest.h>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_add)
{
    REGISTER(left, 1, 1, false, 1);
    REGISTER(right, 1, 1, false, 1);
    REGISTER(out, 1, 1, false, WORD5);
    asm_add(rregister(left), rregister(right), out);
}
