#include "../common.hpp"

TEST(integer_ctor, build)
{
    ap_uint_l a{};
    ap_uint_s b{};
    ap_sint_l c{};
    ap_sint_s d{};

    ASSERT_EQ(ap_uint_l::bitwidth, AP_CAP_L);
    ASSERT_EQ(ap_uint_l::wordwidth, ap_capw(AP_CAP_L));
    ASSERT_EQ(ap_uint_l::valuewidth, AP_CAP_L);
    ASSERT_EQ(ap_uint_l::is_signed, 0);

    ASSERT_EQ(ap_uint_s::bitwidth, AP_CAP_S);
    ASSERT_EQ(ap_uint_s::wordwidth, ap_capw(AP_CAP_S));
    ASSERT_EQ(ap_uint_s::valuewidth, AP_CAP_S);
    ASSERT_EQ(ap_uint_s::is_signed, 0);

    ASSERT_EQ(ap_sint_l::bitwidth, AP_CAP_L);
    ASSERT_EQ(ap_sint_l::wordwidth, ap_capw(AP_CAP_L));
    ASSERT_EQ(ap_sint_l::valuewidth, AP_CAP_L - 1);
    ASSERT_EQ(ap_sint_l::is_signed, 1);

    ASSERT_EQ(ap_sint_s::bitwidth, AP_CAP_S);
    ASSERT_EQ(ap_sint_s::wordwidth, ap_capw(AP_CAP_S));
    ASSERT_EQ(ap_sint_s::valuewidth, AP_CAP_S - 1);
    ASSERT_EQ(ap_sint_s::is_signed, 1);

    wider_int_t<ap_uint_l, ap_uint_l> e1;
    wider_int_t<ap_uint_l, ap_uint_s> e2;
    wider_int_t<ap_sint_l, ap_uint_l> e3;
    wider_int_t<ap_uint_l, ap_sint_l> e4;
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(e1)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(e2)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(e3)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(e4)>::value));

    wider_int_t<ap_uint_s, ap_uint_l> f1;
    wider_int_t<ap_uint_s, ap_uint_s> f2;
    wider_int_t<ap_uint_s, ap_sint_l> f3;
    wider_int_t<ap_uint_s, ap_sint_s> f4;
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(f1)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_s, decltype(f2)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_l, decltype(f3)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_s, decltype(f4)>::value));

    wider_int_t<ap_sint_l, ap_uint_l> g1;
    wider_int_t<ap_sint_l, ap_uint_s> g2;
    wider_int_t<ap_sint_l, ap_sint_l> g3;
    wider_int_t<ap_sint_l, ap_sint_s> g4;
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(g1)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_l, decltype(g2)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_l, decltype(g3)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_l, decltype(g4)>::value));

    wider_int_t<ap_sint_s, ap_uint_l> h1;
    wider_int_t<ap_sint_s, ap_uint_s> h2;
    wider_int_t<ap_sint_s, ap_sint_l> h3;
    wider_int_t<ap_sint_s, ap_sint_s> h4;
    ASSERT_TRUE((std::is_same<ap_uint_l, decltype(h1)>::value));
    ASSERT_TRUE((std::is_same<ap_uint_s, decltype(h2)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_l, decltype(h3)>::value));
    ASSERT_TRUE((std::is_same<ap_sint_s, decltype(h4)>::value));

    ASSERT_EQ(int(a), 0);
}
