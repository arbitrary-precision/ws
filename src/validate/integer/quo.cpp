#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_quo_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left / right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left / right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_quo_impl_u : integer_quo_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_quo_impl_s : integer_quo_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_quox_impl_u : integer_quo_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_quox_impl_s : integer_quo_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_quo_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    return boost_uint_tou(left / right, MAX(lc, rc));
}

static inline std::string boost_integer_quo_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint left{ap_ts(lstr, lc)};
    boost_sint right{ap_ts(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    boost_uint out{left / right};
    return boost_uint_tos(out, MAX(lc, rc));
}

static inline std::string boost_integer_quox_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc >= rc)
    {
        boost_uint left{ap_tu(lstr, lc)};
        boost_uint right{ap_tu(ap_ts(rstr, rc), lc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left / right, lc);
    }
    else
    {
        boost_sint left{ap_tu(lstr, lc)};
        boost_sint right{ap_ts(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left / right};
        return boost_uint_tos(out, rc);
    }
}

static inline std::string boost_integer_quox_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc > rc)
    {
        boost_sint left{ap_ts(lstr, lc)};
        boost_sint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left / right};
        return boost_uint_tos(out, lc);
    }
    else
    {
        boost_uint left{ap_tu(ap_ts(lstr, lc), rc)};
        boost_uint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left / right, rc);
    }
}

static inline std::string ap_integer_quo_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_quo_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_quo_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_quo_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_quox_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_quox_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_quox_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_quox_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_quo, s);
TEST_SUITE_BOPERATOR(integer_quo, u);
TEST_SUITE_BOPERATOR(integer_quox, s);
TEST_SUITE_BOPERATOR(integer_quox, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_squo_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left /= right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left /= right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_squo_impl_u : integer_squo_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_squo_impl_s : integer_squo_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_squox_impl_u : integer_squo_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_squox_impl_s : integer_squo_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_squo_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    return boost_uint_tou(left /= right, lc);
}

static inline std::string boost_integer_squo_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint left{ap_ts(lstr, lc)};
    boost_sint right{ap_ts(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    boost_uint out{left /= right};
    return boost_uint_tos(out, lc);
}

static inline std::string boost_integer_squox_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc >= rc)
    {
        boost_uint left{ap_tu(lstr, lc)};
        boost_uint right{ap_tu(ap_ts(rstr, rc), lc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left /= right, lc);
    }
    else
    {
        boost_sint left{ap_tu(lstr, lc)};
        boost_sint right{ap_ts(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left /= right};
        return boost_uint_tou(out, lc);
    }
}

static inline std::string boost_integer_squox_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc > rc)
    {
        boost_sint left{ap_ts(lstr, lc)};
        boost_sint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left /= right};
        return boost_uint_tos(out, lc);
    }
    else
    {
        boost_uint left{ap_tu(ap_ts(lstr, lc), rc)};
        boost_uint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tos(left /= right, lc);
    }
}

static inline std::string ap_integer_squo_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_squo_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_squo_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_squo_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_squox_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_squox_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_squox_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_squox_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_squo, s);
TEST_SUITE_BOPERATOR(integer_squo, u);
TEST_SUITE_BOPERATOR(integer_squox, s);
TEST_SUITE_BOPERATOR(integer_squox, u);