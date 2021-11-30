#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_sint_tstr)
{
    REGISTER(in, 1, 1, false, 1);
    sint_tstr(rregister(in), 1, "1");
}
