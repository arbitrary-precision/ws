#include <boost/multiprecision/cpp_int.hpp>
#include <ap/ap.hpp>
#include <chronometer/chronometer.hpp>

#define TESTCOUNT 10000

template <std::size_t Size>
using boost_uint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<Size, Size, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;

std::string operand(std::size_t maxhex)
{
    const char* digits = "0123456789ABCDEF";
    maxhex = maxhex / 2 + rand() % (maxhex / 2);
    std::string result;
    result.push_back(digits[rand() % 15 + 1]);
    for (std::size_t i = 1; i < maxhex; ++i)
    {
        result.push_back(digits[rand() % 16]); 
    }
    return "0x" + result;
}

#define MEASURE_OPERATOR(name, op, size)                                        \
    std::pair<unsigned long long, unsigned long long> measure_##name##_##size() \
    {                                                                           \
        std::string left{operand(size / 4)};                                    \
        std::string right{operand(size / 8)};                                   \
        boost_uint<size> bleft{left};                                           \
        boost_uint<size> bright{right};                                         \
        ap_uint<size> aleft{left};                                              \
        ap_uint<size> aright{right};                                            \
        std::pair<unsigned long long, unsigned long long> result;               \
        result.first = chronometer::measure([&]() { aleft op aright; });        \
        result.second = chronometer::measure([&]() { bleft op bright; });       \
        return result;                                                          \
    }

#define MEASURE_OPERATOR_SHIFT(name, op, size)                                  \
    std::pair<unsigned long long, unsigned long long> measure_##name##_##size() \
    {                                                                           \
        std::string left{operand(size / 2)};                                    \
        boost_uint<size> bleft{left};                                           \
        std::size_t shift = rand() % 31 + 1;                                    \
        ap_uint<size> aleft{left};                                              \
        std::pair<unsigned long long, unsigned long long> result;               \
        result.first = chronometer::measure([&]() { aleft op shift; });         \
        result.second = chronometer::measure([&]() { bleft op shift; });        \
        return result;                                                          \
    }

#define MEASURE_OPERATOR_ALL(size)        \
    MEASURE_OPERATOR(add, +, size)       \
    MEASURE_OPERATOR(sub, -, size)       \
    MEASURE_OPERATOR(mul, *, size)       \
    MEASURE_OPERATOR(quo, /, size)       \
    MEASURE_OPERATOR(rem, %, size)       \
    MEASURE_OPERATOR_SHIFT(lsh, <<, size) \
    MEASURE_OPERATOR_SHIFT(rsh, >>, size)

#define RUN_MEASURE(name, size)                                                     \
    std::pair<unsigned long long, unsigned long long> result_##name##_##size{0, 0}; \
    std::pair<unsigned long long, unsigned long long> tmpres_##name##_##size{0, 0}; \
    std::cout << "Measuring " #name " with size " #size ": ";                       \
    for (int i = 0; i < 100; ++i)                                                   \
    {                                                                               \
        /*Warm up*/                                                                 \
        tmpres_##name##_##size = measure_##name##_##size();                         \
    }                                                                               \
    for (int i = 0; i < TESTCOUNT; ++i)                                             \
    {                                                                               \
        tmpres_##name##_##size = measure_##name##_##size();                         \
        result_##name##_##size.first += tmpres_##name##_##size.first;               \
        result_##name##_##size.second += tmpres_##name##_##size.second;             \
    }                                                                               \
    std::cout << "AP: " << result_##name##_##size.first << "; Boost: " << result_##name##_##size.second << "; AP/Boost = " << double(result_##name##_##size.first) / double(result_##name##_##size.second) << std::endl;

MEASURE_OPERATOR_ALL(128)
MEASURE_OPERATOR_ALL(512)
MEASURE_OPERATOR_ALL(4096)
MEASURE_OPERATOR_ALL(10240)

#define RUN_MEASURE_ALL(size) \
    RUN_MEASURE(add, size)    \
    RUN_MEASURE(sub, size)    \
    RUN_MEASURE(mul, size)    \
    RUN_MEASURE(quo, size)    \
    RUN_MEASURE(rem, size)    \
    RUN_MEASURE(lsh, size)    \
    RUN_MEASURE(rsh, size)

#define SEP "======================================================================================\n"

int main()
{
    std::pair<unsigned long long, unsigned long long> result{0, 0};
    std::pair<unsigned long long, unsigned long long> tmpres{0, 0};
    RUN_MEASURE_ALL(128);
    std::cout << SEP;
    RUN_MEASURE_ALL(512);
    std::cout << SEP;
    RUN_MEASURE_ALL(4096);
    std::cout << SEP;
    RUN_MEASURE_ALL(10240);
    return 0;
}