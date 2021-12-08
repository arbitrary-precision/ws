#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_lsh_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        integer<_CapacityL, _Signed> left{lstr};
        unsigned long long int shift = to_ull(rstr);
        return (left << shift).str(16);
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_lsh_impl_u : integer_lsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_lsh_impl_s : integer_lsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

static inline std::string boost_integer_lsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov = lv << rv;
    return boost_uint_tou(ov, lc);
}

static inline std::string boost_integer_lsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov{lv << rv};
    return boost_uint_tos(ov, lc);
}

static inline std::string ap_integer_lsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_lsh_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_lsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_lsh_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_lsh, s);
TEST_SUITE_BOPERATOR(integer_lsh, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_slsh_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        integer<_CapacityL, _Signed> left{lstr};
        unsigned long long int shift = to_ull(rstr);
        return (left <<= shift).str(16);
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_slsh_impl_u : integer_slsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_slsh_impl_s : integer_slsh_impl<_CapacityL, _CapacityR, _Signed>
{
};

static inline std::string boost_integer_slsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov = (lv <<= rv);
    return boost_uint_tou(ov, lc);
}

static inline std::string boost_integer_slsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint lv{lstr};
    index_t rv = to_ull(rstr);
    if (rv > AP_CAP_L)
    {
        return "0x0";
    }
    boost_uint ov{lv <<= rv};
    return boost_uint_tos(ov, lc);
}

static inline std::string ap_integer_slsh_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_slsh_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_slsh_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_slsh_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_slsh, s);
TEST_SUITE_BOPERATOR(integer_slsh, u);
