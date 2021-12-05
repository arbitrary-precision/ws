#include "../common.hpp"

static inline std::string bapi_mul_u(const std::string& lstr, const std::string& rstr)
{
    boost_uint lv;
    boost_uint rv;
    lv.assign(lstr);
    rv.assign(rstr);
    boost_uint ov = lv * rv;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_mul_s(const std::string& lstr, const std::string& rstr)
{
    return bapi_mul_u(lstr, rstr);
}

static inline std::string xapi_mul_u(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    uapi_mul(rregister(l), rregister(r), o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_mul_s(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    sapi_mul(rregister(l), rregister(r), o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_mul, build)
{
    AP_REGISTER(l, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcap(apt_cap::CMAX), 0, false);
    uapi_mul(rregister(l), rregister(r), o);
    sapi_mul(rregister(l), rregister(r), o);
}

TEST_BIN_OP_SUITE(mxuu, mul, u, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, mul, u, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, mul, u, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxuu, mul, s, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, mul, s, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, mul, s, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxus, mul, s, apt_cap::CMAX, AP_P, AP_N);
TEST_BIN_OP_SUITE(mdus, mul, s, apt_cap::CMID, AP_P, AP_N);
TEST_BIN_OP_SUITE(mnus, mul, s, apt_cap::CMIN, AP_P, AP_N);
TEST_BIN_OP_SUITE(mxsu, mul, s, apt_cap::CMAX, AP_N, AP_P);
TEST_BIN_OP_SUITE(mdsu, mul, s, apt_cap::CMID, AP_N, AP_P);
TEST_BIN_OP_SUITE(mnsu, mul, s, apt_cap::CMIN, AP_N, AP_P);
TEST_BIN_OP_SUITE(mxss, mul, s, apt_cap::CMAX, AP_N, AP_N);
TEST_BIN_OP_SUITE(mdss, mul, s, apt_cap::CMID, AP_N, AP_N);
TEST_BIN_OP_SUITE(mnss, mul, s, apt_cap::CMIN, AP_N, AP_N);
