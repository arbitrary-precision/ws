#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_and_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left & right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left & right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_and_impl_u : integer_and_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_and_impl_s : integer_and_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_andx_impl_u : integer_and_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_andx_impl_s : integer_and_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_and_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left & right, MAX(lc, rc));
}

static inline std::string boost_integer_and_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left & right, MAX(lc, rc));
}

static inline std::string boost_integer_andx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    if (lc >= rc)
    {
        return boost_uint_tou(left & right, lc);
    }
    else
    {
        return boost_uint_tos(left & right, rc);
    }
}

static inline std::string boost_integer_andx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (lc > rc)
    {
        return boost_uint_tos(left & right, lc);
    }
    else
    {
        return boost_uint_tou(left & right, rc);
    }
}

static inline std::string ap_integer_and_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_and_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_and_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_and_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_andx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_andx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_andx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_andx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_and, s);
TEST_SUITE_BOPERATOR(integer_and, u);
TEST_SUITE_BOPERATOR(integer_andx, s);
TEST_SUITE_BOPERATOR(integer_andx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_sand_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left &= right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left &= right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sand_impl_u : integer_sand_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sand_impl_s : integer_sand_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sandx_impl_u : integer_sand_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sandx_impl_s : integer_sand_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_sand_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left &= right, lc);
}

static inline std::string boost_integer_sand_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left &= right, lc);
}

static inline std::string boost_integer_sandx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tou(left &= right, lc);
}

static inline std::string boost_integer_sandx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tos(left &= right, lc);
}

static inline std::string ap_integer_sand_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sand_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sand_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sand_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sandx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sandx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sandx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sandx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_sand, s);
TEST_SUITE_BOPERATOR(integer_sand, u);
TEST_SUITE_BOPERATOR(integer_sandx, s);
TEST_SUITE_BOPERATOR(integer_sandx, u);
