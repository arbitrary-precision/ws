#include "../common.hpp"

static inline std::string bapi_tstr_u(const std::string& istr)
{
    boost_uint v;
    v.assign(istr);
    boost_uint ov = v;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_tstr_s(const std::string& istr)
{
    return bapi_tstr_u(istr);
}

static inline std::string xapi_tstr_u(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(c), 0, false);
    uapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    uapi_tstr(rregister(i), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_tstr_s(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(c), 0, false);
    sapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    sapi_tstr(rregister(i), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_tstr, build)
{
    AP_REGISTER(i, 1, 0, false);
    std::string o;
    uapi_tstr(rregister(i), o, 16, "0123456789ABCDEF");
    sapi_tstr(rregister(i), o, 16, "0123456789ABCDEF");
}

TEST_UN_OP_SUITE(mxu, tstr, u, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tstr, u, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tstr, u, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxu, tstr, s, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tstr, s, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tstr, s, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxs, tstr, s, apt_cap::CMAX, AP_N);
TEST_UN_OP_SUITE(mds, tstr, s, apt_cap::CMID, AP_N);
TEST_UN_OP_SUITE(mns, tstr, s, apt_cap::CMIN, AP_N);
