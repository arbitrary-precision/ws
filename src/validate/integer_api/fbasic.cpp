#include "../common.hpp"

static inline std::string boost_xinteger_fbasic_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16)};
    return boost_uint_tou(v, oc);
}

static inline std::string boost_xinteger_fbasic_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{std::stoll(ap_ts(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16)};
    return boost_uint_tos(v, oc);
}

static inline std::string ap_xinteger_fbasic_u(const std::string& istr, index_t ic, index_t oc)
{
    std::string result;
    AP_REGISTER_D(ov, ap_capw(oc));
    unsigned long long v = std::stoull(ap_tu(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
    uinteger_fbasic(ov, v);
    uinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string ap_xinteger_fbasic_s(const std::string& istr, index_t ic, index_t oc)
{
    std::string result;
    AP_REGISTER_D(ov, ap_capw(oc));
    signed long long v = std::stoll(ap_ts(istr, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
    sinteger_fbasic(ov, v);
    sinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

TEST_SUITE_UOP(xinteger_fbasic, s);
TEST_SUITE_UOP(xinteger_fbasic, u);
