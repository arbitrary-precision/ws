#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_sint_lsh)
{
    REGISTER(left, 1, 1, false, 1);
    REGISTER(out, 1, 1, false, WORD5);
    sint_lsh(rregister(left), 1, out);
}
