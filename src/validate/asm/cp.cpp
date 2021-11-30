#include <gtest/gtest.h>
#include <ap/asm.hpp>
#include "../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_cp)
{
    REGISTER(in, 1, 1, false, 1);
    REGISTER(out, 1, 1, false, WORD5);
    asm_cp(rregister(in), out);
}
