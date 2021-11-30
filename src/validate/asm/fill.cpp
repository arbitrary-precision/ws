#include "../utils.hpp"
#include <ap/asm.hpp>
#include <gtest/gtest.h>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_fill)
{
    REGISTER(inout, 1, 1, false, 1);
    asm_fill(inout, 0);
}
