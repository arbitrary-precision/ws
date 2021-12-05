#include "../common.hpp"

static inline std::string bapi_scp_u(const std::string& istr)
{
    boost_uint v;
    v.assign(istr);
    boost_uint ov = v;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_scp_s(const std::string& istr)
{
    return bapi_scp_u(istr);
}

static inline std::string xapi_scp_u(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    uapi_scp(rregister(i), o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_scp_s(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    sapi_scp(rregister(i), o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_scp, build)
{
    AP_REGISTER(i, 1, 0, false);
    AP_REGISTER(o, 1, 0, false);
    uapi_scp(rregister(i), o);
    sapi_scp(rregister(i), o);
}

TEST_UN_OP_SUITE(mxu, scp, u, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, scp, u, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, scp, u, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxu, scp, s, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, scp, s, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, scp, s, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxs, scp, s, apt_cap::CMAX, AP_N);
TEST_UN_OP_SUITE(mds, scp, s, apt_cap::CMID, AP_N);
TEST_UN_OP_SUITE(mns, scp, s, apt_cap::CMIN, AP_N);
