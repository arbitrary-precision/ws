#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_add_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left + right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left + right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_add_impl_u : integer_add_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_add_impl_s : integer_add_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_addx_impl_u : integer_add_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_addx_impl_s : integer_add_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_add_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left + right, MAX(lc, rc));
}

static inline std::string boost_integer_add_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left + right, MAX(lc, rc));
}

static inline std::string boost_integer_addx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    if (lc >= rc)
    {
        return boost_uint_tou(left + right, lc);
    }
    else
    {
        return boost_uint_tos(left + right, rc);
    }
}

static inline std::string boost_integer_addx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (lc > rc)
    {
        return boost_uint_tos(left + right, lc);
    }
    else
    {
        return boost_uint_tou(left + right, rc);
    }
}

static inline std::string ap_integer_add_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_add_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_add_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_add_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_addx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_addx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_addx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_addx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_add, s);
TEST_SUITE_BOPERATOR(integer_add, u);
TEST_SUITE_BOPERATOR(integer_addx, s);
TEST_SUITE_BOPERATOR(integer_addx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_sadd_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left += right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left += right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sadd_impl_u : integer_sadd_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sadd_impl_s : integer_sadd_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_saddx_impl_u : integer_sadd_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_saddx_impl_s : integer_sadd_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_sadd_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left += right, lc);
}

static inline std::string boost_integer_sadd_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left += right, lc);
}

static inline std::string boost_integer_saddx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tou(left += right, lc);
}

static inline std::string boost_integer_saddx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tos(left += right, lc);
}

static inline std::string ap_integer_sadd_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sadd_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sadd_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sadd_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_saddx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_saddx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_saddx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_saddx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_sadd, s);
TEST_SUITE_BOPERATOR(integer_sadd, u);
TEST_SUITE_BOPERATOR(integer_saddx, s);
TEST_SUITE_BOPERATOR(integer_saddx, u);
