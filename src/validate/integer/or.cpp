#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_or_impl
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
struct integer_or_impl_u : integer_or_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_or_impl_s : integer_or_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_orx_impl_u : integer_or_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_orx_impl_s : integer_or_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_or_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left ^ right, MAX(lc, rc));
}

static inline std::string boost_integer_or_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left ^ right, MAX(lc, rc));
}

static inline std::string boost_integer_orx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
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

static inline std::string boost_integer_orx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
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

static inline std::string ap_integer_or_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_or_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_or_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_or_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_orx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_orx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_orx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_orx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_or, s);
TEST_SUITE_BOPERATOR(integer_or, u);
TEST_SUITE_BOPERATOR(integer_orx, s);
TEST_SUITE_BOPERATOR(integer_orx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_sor_impl
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
struct integer_sor_impl_u : integer_sor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sor_impl_s : integer_sor_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sorx_impl_u : integer_sor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sorx_impl_s : integer_sor_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_sor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left ^= right, lc);
}

static inline std::string boost_integer_sor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left ^= right, lc);
}

static inline std::string boost_integer_sorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tou(left ^= right, lc);
}

static inline std::string boost_integer_sorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tos(left ^= right, lc);
}

static inline std::string ap_integer_sor_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sor_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sor_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sor_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sorx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sorx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sorx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sorx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_sor, s);
TEST_SUITE_BOPERATOR(integer_sor, u);
TEST_SUITE_BOPERATOR(integer_sorx, s);
TEST_SUITE_BOPERATOR(integer_sorx, u);
