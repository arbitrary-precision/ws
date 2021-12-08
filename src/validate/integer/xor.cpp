#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_xor_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left ^ right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left ^ right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_xor_impl_u : integer_xor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_xor_impl_s : integer_xor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_xorx_impl_u : integer_xor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_xorx_impl_s : integer_xor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_xor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left ^ right, MAX(lc, rc));
}

static inline std::string boost_integer_xor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left ^ right, MAX(lc, rc));
}

static inline std::string boost_integer_xorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    if (lc >= rc)
    {
        return boost_uint_tou(left ^ right, lc);
    }
    else
    {
        return boost_uint_tos(left ^ right, rc);
    }
}

static inline std::string boost_integer_xorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (lc > rc)
    {
        return boost_uint_tos(left ^ right, lc);
    }
    else
    {
        return boost_uint_tou(left ^ right, rc);
    }
}

static inline std::string ap_integer_xor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_xor_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_xor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_xor_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_xorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_xorx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_xorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_xorx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_xor, s);
TEST_SUITE_BOPERATOR(integer_xor, u);
TEST_SUITE_BOPERATOR(integer_xorx, s);
TEST_SUITE_BOPERATOR(integer_xorx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_sxor_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left ^= right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left ^= right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sxor_impl_u : integer_sxor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sxor_impl_s : integer_sxor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sxorx_impl_u : integer_sxor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sxorx_impl_s : integer_sxor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_sxor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left ^= right, lc);
}

static inline std::string boost_integer_sxor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left ^= right, lc);
}

static inline std::string boost_integer_sxorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tou(left ^= right, lc);
}

static inline std::string boost_integer_sxorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tos(left ^= right, lc);
}

static inline std::string ap_integer_sxor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sxor_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sxor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sxor_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sxorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sxorx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sxorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sxorx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_sxor, s);
TEST_SUITE_BOPERATOR(integer_sxor, u);
TEST_SUITE_BOPERATOR(integer_sxorx, s);
TEST_SUITE_BOPERATOR(integer_sxorx, u);
