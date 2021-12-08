#include "../common.hpp"

static inline index_t toshift(const std::string& str)
{
    return std::stoull(ap_tu(str, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
}

static inline std::string boost_xinteger_rsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = toshift(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov = lv >> rv;
    return boost_uint_tou(ov, oc);
}

static inline std::string boost_xinteger_rsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint lv{lstr};
    index_t rv = toshift(rstr);
    if (rv > AP_CAP_L)
    {
        if (lv < 0)
        {
            return "-0x1";
        }
        else
        {
            return "0x0";
        }
    }
    boost_uint ov{lv >> rv};
    return boost_uint_tos(ov, oc);
}

static inline std::string ap_xinteger_rsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    index_t rv = toshift(rstr);
    AP_REGISTER_D(ov, ap_capw(oc));
    uinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uinteger_rsh(rregister(lv), rv, ov);
    uinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string ap_xinteger_rsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;
    AP_REGISTER_D(lv, ap_capw(lc));
    index_t rv = toshift(rstr);
    AP_REGISTER_D(ov, ap_capw(oc));
    sinteger_fstr(lv, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sinteger_rsh(rregister(lv), rv, ov);
    sinteger_tstr(rregister(ov), result, 16, "0123456789ABCDEF");
    return result;
}

TEST_SUITE_BOP(xinteger_rsh, s);
TEST_SUITE_BOP(xinteger_rsh, u);
