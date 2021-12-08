#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_rsh_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        integer<_CapacityL, _Signed> left{lstr};
        unsigned long long int shift = to_ull(rstr);
        return (left >> shift).str(16);
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_rsh_impl_u : integer_rsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_rsh_impl_s : integer_rsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

static inline std::string boost_integer_rsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov = lv >> rv;
    return boost_uint_tou(ov, lc);
}

static inline std::string boost_integer_rsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint lv{lstr};
    index_t rv = to_ull(rstr);
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
    return boost_uint_tos(ov, lc);
}

static inline std::string ap_integer_rsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_rsh_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_rsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_rsh_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_rsh, s);
TEST_SUITE_BOPERATOR(integer_rsh, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_srsh_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        integer<_CapacityL, _Signed> left{lstr};
        unsigned long long int shift = to_ull(rstr);
        return (left >>= shift).str(16);
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_srsh_impl_u : integer_srsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_srsh_impl_s : integer_srsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

static inline std::string boost_integer_srsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov = (lv >>= rv);
    return boost_uint_tou(ov, lc);
}

static inline std::string boost_integer_srsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint lv{lstr};
    index_t rv = to_ull(rstr);
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
    boost_uint ov{lv >>= rv};
    return boost_uint_tos(ov, lc);
}

static inline std::string ap_integer_srsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_srsh_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_srsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_srsh_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_srsh, s);
TEST_SUITE_BOPERATOR(integer_srsh, u);
