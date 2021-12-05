#include "../common.hpp"

static inline std::string bapi_tos_u(const std::string& istr)
{
    boost_uint v;
    v.assign(istr);
    boost_int ov = v;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_tos_s(const std::string& istr)
{
    return bapi_tos_u(istr);
}

static inline std::string xapi_tos_u(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    uapi_tos(rregister(i), o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    if (result[0] == '-')
    {
        return apt_stru(result.substr(1, result.size() - 1), c, apt_size::SF, true);
    }
    return result;
}

static inline std::string xapi_tos_s(const std::string& istr, apt_cap c)
{
    throw std::runtime_error{"xapi_tos_s not implemented."};
}

TEST(xapi_tos, build)
{
    AP_REGISTER(i, 1, 0, false);
    AP_REGISTER(o, 1, 0, false);
    uapi_tos(rregister(i), o);
}

TEST_UN_OP_SUITE(mxu, tos, u, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tos, u, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tos, u, apt_cap::CMIN, AP_P);
