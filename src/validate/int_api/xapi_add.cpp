#include "../common.hpp"

static inline std::string bapi_add_u(const std::string& lstr, const std::string& rstr)
{
    boost_uint lv;
    boost_uint rv;
    lv.assign(lstr);
    rv.assign(rstr);
    boost_uint ov = lv + rv;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_add_s(const std::string& lstr, const std::string& rstr)
{
    return bapi_add_u(lstr, rstr);
}

static inline std::string xapi_add_u(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    uapi_add(rregister(l), rregister(r), o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_add_s(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    sapi_add(rregister(l), rregister(r), o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_add, build)
{
    AP_REGISTER(l, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcap(apt_cap::CMAX), 0, false);
    uapi_add(rregister(l), rregister(r), o);
    sapi_add(rregister(l), rregister(r), o);
}

TEST_BIN_OP_SUITE(mxuu, add, u, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, add, u, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, add, u, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxuu, add, s, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, add, s, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, add, s, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxus, add, s, apt_cap::CMAX, AP_P, AP_N);
TEST_BIN_OP_SUITE(mdus, add, s, apt_cap::CMID, AP_P, AP_N);
TEST_BIN_OP_SUITE(mnus, add, s, apt_cap::CMIN, AP_P, AP_N);
TEST_BIN_OP_SUITE(mxsu, add, s, apt_cap::CMAX, AP_N, AP_P);
TEST_BIN_OP_SUITE(mdsu, add, s, apt_cap::CMID, AP_N, AP_P);
TEST_BIN_OP_SUITE(mnsu, add, s, apt_cap::CMIN, AP_N, AP_P);
TEST_BIN_OP_SUITE(mxss, add, s, apt_cap::CMAX, AP_N, AP_N);
TEST_BIN_OP_SUITE(mdss, add, s, apt_cap::CMID, AP_N, AP_N);
TEST_BIN_OP_SUITE(mnss, add, s, apt_cap::CMIN, AP_N, AP_N);
