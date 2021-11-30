#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_sint_fstr)
{
    REGISTER(out, 1, 1, false, WORD5);
    sint_fstr(out, "1", 1, "1");
}
