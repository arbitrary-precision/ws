#include <gtest/gtest.h>
#include <ap/asm.hpp>
#include "../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_cmp)
{
    REGISTER(left, 1, 1, false, 1);
    REGISTER(right, 1, 1, false, 1);
    asm_cmp(rregister(left), rregister(right));
}
