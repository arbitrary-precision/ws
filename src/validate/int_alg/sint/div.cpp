#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_sint_div)
{
    REGISTER(left, 2, 2, false, 1, 1);
    REGISTER(right, 2, 2, false, 1, 1);
    REGISTER(quo, 2, 2, false, WORD5, WORD5);
    REGISTER(rem, 2, 2, false, WORD5, WORD5);
    sint_div(rregister(left), rregister(right), quo, rem);
}
