#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_uint_add)
{
    REGISTER(left, 1, 1, false, 1);
    REGISTER(right, 1, 1, false, 1);
    REGISTER(out, 1, 1, false, WORD5);
    uint_add(rregister(left), rregister(right), out);
}
