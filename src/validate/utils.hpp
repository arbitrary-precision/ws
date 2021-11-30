#ifndef DEOHAYER_AP_VALIDATE_UTILS_HPP
#define DEOHAYER_AP_VALIDATE_UTILS_HPP

#define REGISTER(name, capacity, size, sign, ...) \
    word_t name##_arr[capacity] = {__VA_ARGS__};  \
    wregister name { name##_arr, capacity, size, sign }

#define REGISTER_EQ(reg1, reg2)                  \
    ASSERT_EQ(reg1.sign, reg2.sign);             \
    ASSERT_EQ(reg1.capacity, reg2.capacity);     \
    ASSERT_EQ(reg1.size, reg2.size);             \
    for (index_t i = 0; i < reg1.size; ++i)      \
    {                                            \
        ASSERT_EQ(reg1.words[i], reg2.words[i]); \
    }                                            \
    (void)0

#define BASE (dword_t{word_traits::ones} + 1)
#define HBASE (word_t(BASE / 2))
#define HBITS (word_traits::bits / 2)

#define WORD0 (word_traits::zeros)
#define WORD1 (word_traits::ones)
#define WORD5 (word_t(0x55555555))
#define WORDA (word_t(0xAAAAAAAA))

#define WORDL (word_t(word_traits::ones << 1))
#define WORDR (word_t(word_traits::ones >> 1))
#define WORDE (word_t(word_traits::ones << HBITS))
#define WORDY (word_t(word_traits::ones >> HBITS))

#endif
