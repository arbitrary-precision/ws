#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_uint_fstr)
{
    REGISTER(out, 1, 1, false, WORD5);
    uint_fstr(out, "1", 1, "1");
}
