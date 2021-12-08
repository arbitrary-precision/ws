#include "../common.hpp"

static inline std::string boost_xinteger_not_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    v = ~v;
    return boost_uint_tou(v, oc);
}

static inline std::string boost_xinteger_not_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    v = ~v;
    return boost_uint_tos(v, oc);
}

static inline std::string ap_xinteger_not_u(const std::string& istr, index_t ic, index_t oc)
{
    std::string result;
    AP_REGISTER_D(iv, ap_capw(ic));
    AP_REGISTER_D(ov, ap_capw(oc));
    uinteger_fstr(iv, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    uinteger_not(rregister(iv), ov);
    uinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string ap_xinteger_not_s(const std::string& istr, index_t ic, index_t oc)
{
    std::string result;
    AP_REGISTER_D(iv, ap_capw(ic));
    AP_REGISTER_D(ov, ap_capw(oc));
    sinteger_fstr(iv, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    sinteger_not(rregister(iv), ov);
    sinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

TEST_SUITE_UOP(xinteger_not, s);
TEST_SUITE_UOP(xinteger_not, u);
