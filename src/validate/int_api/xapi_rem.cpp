#include "../common.hpp"

static inline std::string bapi_rem_u(const std::string& l, const std::string& r)
{
    boost_uint lv;
    boost_uint rv;
    lv.assign(l);
    rv.assign(r);
    if (rv == 0)
    {
        return "0x0";
    }
    boost_uint ov = lv % rv;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_rem_s(const std::string& l, const std::string& r)
{
    boost_int lv;
    boost_int rv;
    lv.assign(apt_strs(l, apt_cap::CMAX, apt_size::SF));
    rv.assign(apt_strs(r, apt_cap::CMAX, apt_size::SF));
    if (rv == 0)
    {
        return "0x0";
    }
    boost_int ov = lv % rv;
    boost_uint ovu;
    ovu.assign(ov);
    return std::string("0x") + ovu.str(0, std::ios_base::hex);
}

static inline std::string xapi_rem_u(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    uapi_rem(rregister(l), rregister(r), o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_rem_s(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sapi_fstr(r, rstr.c_str(), rstr.size(), 16, "0123456789ABCDEF");
    sapi_rem(rregister(l), rregister(r), o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_rem, build)
{
    AP_REGISTER(l, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(r, apt_gcap(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcap(apt_cap::CMAX), 0, false);
    uapi_rem(rregister(l), rregister(r), o);
    sapi_rem(rregister(l), rregister(r), o);
}

TEST_BIN_OP_SUITE(mxuu, rem, u, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, rem, u, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, rem, u, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxuu, rem, s, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, rem, s, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, rem, s, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxus, rem, s, apt_cap::CMAX, AP_P, AP_N);
TEST_BIN_OP_SUITE(mdus, rem, s, apt_cap::CMID, AP_P, AP_N);
TEST_BIN_OP_SUITE(mnus, rem, s, apt_cap::CMIN, AP_P, AP_N);
TEST_BIN_OP_SUITE(mxsu, rem, s, apt_cap::CMAX, AP_N, AP_P);
TEST_BIN_OP_SUITE(mdsu, rem, s, apt_cap::CMID, AP_N, AP_P);
TEST_BIN_OP_SUITE(mnsu, rem, s, apt_cap::CMIN, AP_N, AP_P);
TEST_BIN_OP_SUITE(mxss, rem, s, apt_cap::CMAX, AP_N, AP_N);
TEST_BIN_OP_SUITE(mdss, rem, s, apt_cap::CMID, AP_N, AP_N);
TEST_BIN_OP_SUITE(mnss, rem, s, apt_cap::CMIN, AP_N, AP_N);
