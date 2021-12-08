#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_move_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        std::string result_ctor;
        std::string result_assign;

        if (_Crossed)
        {
            integer<_CapacityR, !_Signed> other_ctor{lstr};
            integer<_CapacityL, _Signed> this_ctor{std::move(other_ctor)};
            result_ctor = this_ctor.str(16);
            result_assign = this_ctor.str(16);
            integer<_CapacityR, !_Signed> other_assign{lstr};
            integer<_CapacityL, _Signed> this_assign;
            this_assign = std::move(other_assign);
            result_assign = this_assign.str(16);
        }
        else
        {
            integer<_CapacityR, _Signed> other_ctor{lstr};
            integer<_CapacityL, _Signed> this_ctor{std::move(other_ctor)};
            result_ctor = this_ctor.str(16);
            integer<_CapacityR, _Signed> other_assign{lstr};
            integer<_CapacityL, _Signed> this_assign;
            this_assign = std::move(other_assign);
            result_assign = this_assign.str(16);
        }

        if (result_ctor != result_assign)
        {
            std::cout << result_ctor << std::endl;
            std::cout << result_assign << std::endl;
            throw std::runtime_error("result_ctor != result_assign");
        }

        return result_ctor;
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_move_impl_u : integer_move_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_move_impl_s : integer_move_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_movex_impl_u : integer_move_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_movex_impl_s : integer_move_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_move_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_tu(ap_tu(lstr, rc), lc);
}

static inline std::string boost_integer_move_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_ts(ap_ts(lstr, rc), lc);
}

static inline std::string boost_integer_movex_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_tu(ap_ts(lstr, rc), lc);
}

static inline std::string boost_integer_movex_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_ts(ap_tu(lstr, rc), lc);
}

static inline std::string ap_integer_move_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_move_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_move_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_move_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_movex_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_movex_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_movex_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_movex_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_move, s);
TEST_SUITE_BOPERATOR(integer_move, u);
TEST_SUITE_BOPERATOR(integer_movex, s);
TEST_SUITE_BOPERATOR(integer_movex, u);
