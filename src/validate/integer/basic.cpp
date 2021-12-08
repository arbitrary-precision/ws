#include "../common.hpp"

template <index_t _Capacity, bool _Signed, typename T>
struct integer_basic_impl
{
    std::string operator()(const std::string& istr) const
    {
        T val = std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
        integer<_Capacity, _Signed> iov{val};
        val = T(iov);
        return std::to_string(val);
    }
};

template <index_t _Capacity, bool _Signed>
struct integer_basic_impl_u : integer_basic_impl<_Capacity, _Signed, unsigned long long>
{
};

template <index_t _Capacity, bool _Signed>
struct integer_basic_impl_s : integer_basic_impl<_Capacity, _Signed, signed long long>
{
};

static inline std::string boost_integer_basic_u(const std::string& istr, index_t ic, index_t oc)
{
    unsigned long long val = std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
    return std::to_string(val);
}

static inline std::string boost_integer_basic_s(const std::string& istr, index_t ic, index_t oc)
{
    signed long long val = std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
    return std::to_string(val);
}

static inline std::string boost_integer_basicx_u(const std::string& istr, index_t ic, index_t oc)
{
    signed long long val = std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
    return std::to_string(val);
}

static inline std::string ap_integer_basic_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_basic_impl_u>(istr, ic);
}

static inline std::string ap_integer_basic_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_basic_impl_s>(istr, ic);
}

static inline std::string ap_integer_basicx_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_basic_impl_s>(istr, ic);
}

TEST_SUITE_UOP(integer_basic, s);
TEST_SUITE_UOP(integer_basic, u);
TEST_SUITE_UOP(integer_basicx, u);

#define TEST_ALL_BASIC_CONVERSIONS(sgnd)                                     \
    ap_##sgnd##int_l sgnd##ax{static_cast<char>(0)};                         \
    ap_##sgnd##int_l sgnd##a0{static_cast<unsigned char>(1)};                \
    ap_##sgnd##int_l sgnd##a1{static_cast<unsigned>(2)};                     \
    ap_##sgnd##int_l sgnd##a2{static_cast<unsigned short>(3)};               \
    ap_##sgnd##int_l sgnd##a3{static_cast<unsigned long>(4)};                \
    ap_##sgnd##int_l sgnd##a4{static_cast<unsigned long long>(5)};           \
    ap_##sgnd##int_l sgnd##a5{static_cast<signed char>(-1)};                 \
    ap_##sgnd##int_l sgnd##a6{static_cast<signed>(-2)};                      \
    ap_##sgnd##int_l sgnd##a7{static_cast<signed short>(-3)};                \
    ap_##sgnd##int_l sgnd##a8{static_cast<signed long>(-4)};                 \
    ap_##sgnd##int_l sgnd##a9{static_cast<signed long long>(-5)};            \
                                                                             \
    ap_##sgnd##int_l sgnd##bx;                                               \
    ap_##sgnd##int_l sgnd##b0;                                               \
    ap_##sgnd##int_l sgnd##b1;                                               \
    ap_##sgnd##int_l sgnd##b2;                                               \
    ap_##sgnd##int_l sgnd##b3;                                               \
    ap_##sgnd##int_l sgnd##b4;                                               \
    ap_##sgnd##int_l sgnd##b5;                                               \
    ap_##sgnd##int_l sgnd##b6;                                               \
    ap_##sgnd##int_l sgnd##b7;                                               \
    ap_##sgnd##int_l sgnd##b8;                                               \
    ap_##sgnd##int_l sgnd##b9;                                               \
                                                                             \
    sgnd##bx = static_cast<char>(0);                                         \
    sgnd##b0 = static_cast<unsigned char>(1);                                \
    sgnd##b1 = static_cast<unsigned>(2);                                     \
    sgnd##b2 = static_cast<unsigned short>(3);                               \
    sgnd##b3 = static_cast<unsigned long>(4);                                \
    sgnd##b4 = static_cast<unsigned long long>(5);                           \
    sgnd##b5 = static_cast<signed char>(-1);                                 \
    sgnd##b6 = static_cast<signed>(-2);                                      \
    sgnd##b7 = static_cast<signed short>(-3);                                \
    sgnd##b8 = static_cast<signed long>(-4);                                 \
    sgnd##b9 = static_cast<signed long long>(-5);                            \
    char sgnd##cx = static_cast<char>(sgnd##bx);                             \
    unsigned char sgnd##c0 = static_cast<unsigned char>(sgnd##b0);           \
    unsigned sgnd##c1 = static_cast<unsigned>(sgnd##b1);                     \
    unsigned short sgnd##c2 = static_cast<unsigned short>(sgnd##b2);         \
    unsigned long sgnd##c3 = static_cast<unsigned long>(sgnd##b3);           \
    unsigned long long sgnd##c4 = static_cast<unsigned long long>(sgnd##b4); \
    signed char sgnd##c5 = static_cast<signed char>(sgnd##b5);               \
    signed sgnd##c6 = static_cast<signed>(sgnd##b6);                         \
    signed short sgnd##c7 = static_cast<signed short>(sgnd##b7);             \
    signed long sgnd##c8 = static_cast<signed long>(sgnd##b8);               \
    signed long long sgnd##c9 = static_cast<signed long long>(sgnd##b9);     \
    if (bool(sgnd##b9))                                                      \
    {                                                                        \
    }

TEST(integer_basic, build)
{
    TEST_ALL_BASIC_CONVERSIONS(u);
    TEST_ALL_BASIC_CONVERSIONS(s);
}