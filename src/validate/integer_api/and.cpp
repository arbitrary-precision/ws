#include "../common.hpp"

BOOST_BOP(xinteger_and, &, u);
BOOST_BOP(xinteger_and, &, s);

static inline std::string ap_xinteger_and_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    AP_REGISTER_D(rv, ap_capw(rc));
    AP_REGISTER_D(ov, ap_capw(oc));
    uinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uinteger_fstr(rv, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    uinteger_and(rregister(lv), rregister(rv), ov);
    uinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string ap_xinteger_and_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    AP_REGISTER_D(rv, ap_capw(rc));
    AP_REGISTER_D(ov, ap_capw(oc));
    sinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sinteger_fstr(rv, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    sinteger_and(rregister(lv), rregister(rv), ov);
    sinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

TEST_SUITE_BOP(xinteger_and, s);
TEST_SUITE_BOP(xinteger_and, u);
