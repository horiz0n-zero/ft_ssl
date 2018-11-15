#include "des.h"

static const int          g_tables[2][64] =
{
    {58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7},
    {40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25}
};

static uint64_t              permutation(uint64_t block,
                const int *const values)
{
    uint64_t                 r;
    int                      i;

    i = 0;
    r = 0;
    while (i < 64)
    {
        r <<= 1;
        r |= (block >> (64 - values[i])) & LB64_MASK;
        i++;
    }
    return (r);
}

static inline void          des_stel(uint32_t *const l, uint32_t *const r, uint32_t f)
{
    uint32_t                temp;

    temp = *r;
    *r = *l ^ f;
    *l = temp;
}

uint64_t                   des_process(t_des *const des,
                uint64_t block, const int decrypt)
{
    int                     index;
    uint32_t                l;
    uint32_t                r;
    uint32_t                f;

    index = 0;
    block = permutation(block, g_tables[0]);
    l = (uint32_t)(block >> 32) & L64_MASK;
    r = (uint32_t)(block & L64_MASK);
    while (index < 16)
    {
        if (decrypt)
            f = des_f(r, des->subkeys[15 - index]);
        else
            f = des_f(r, des->subkeys[index]);
        des_stel(&l, &r, f);
        index++;
    }
    return (permutation(block, g_tables[1]));
}
