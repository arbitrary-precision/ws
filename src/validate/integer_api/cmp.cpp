#include "../common.hpp"

static inline std::string boost_xinteger_cmp_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    boost_uint rv{rstr};
    boost_uint ov{lv.compare(rv)};
    return boost_uint_tos(ov, 8);
}

static inline std::string boost_xinteger_cmp_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint lv{lstr};
    boost_sint rv{rstr};
    boost_uint ov{lv.compare(rv)};
    return boost_uint_tos(ov, 8);
}

static inline std::string ap_xinteger_cmp_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    AP_REGISTER_D(rv, ap_capw(rc));
    uinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uinteger_fstr(rv, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    boost_uint ov{uinteger_cmp(rregister(lv), rregister(rv)).result};
    return boost_uint_tos(ov, 8);
}

static inline std::string ap_xinteger_cmp_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    AP_REGISTER_D(rv, ap_capw(rc));
    sinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sinteger_fstr(rv, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    boost_uint ov{sinteger_cmp(rregister(lv), rregister(rv)).result};
    return boost_uint_tos(ov, 8);
}

TEST_SUITE_BOP(xinteger_cmp, s);
TEST_SUITE_BOP(xinteger_cmp, u);
