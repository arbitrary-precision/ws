#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_uint_cmp)
{
    REGISTER(left, 1, 1, false, 1);
    REGISTER(right, 1, 1, false, 1);
    uint_cmp(rregister(left), rregister(right));
}
