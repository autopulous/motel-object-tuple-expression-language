#include "motel.aleatory.h"

/* xorshift 1024 pseudo random number generator */

static uint64_t s1024[16];
static int p1024 = 0;

/* The aleatory state must be seeded so that it is not all zeros */

EXPORT_STORAGE_CLASS void CALLING_CONVENTION AleatorySeed1024Period
(
    uint64_t pSeed[16]
)
{
    for (int i = 0; i < 16; i++)
    {
        s1024[i] = pSeed[i];
    }
}

EXPORT_STORAGE_CLASS uint64_t CALLING_CONVENTION Aleatory1024Period
(
    void
)
{
    uint64_t s0 = s1024[p1024];

    p1024 = ++ p1024 & 15;

    uint64_t s1 = s1024[p1024];

    s0 ^= s0 >> 30;

    s1 ^= s1 << 31;
    s1 ^= s1 >> 11;

    s1024[p1024] = s0 ^ s1;

    return (s1024[p1024] * 1181783497276652981LL);
}

/* xorshift 4096 pseudo random number generator */

static uint64_t s4096[64];
static int p4096 = 0;

/* The aleatory state must be seeded so that it is not all zeros */

EXPORT_STORAGE_CLASS void CALLING_CONVENTION AleatorySeed4096Period
(
    uint64_t pSeed[64]
)
{
    for (int i = 0; i < 64; i++)
    {
        s4096[i] = pSeed[i];
    }
}

EXPORT_STORAGE_CLASS uint64_t CALLING_CONVENTION Aleatory4096Period
(
    void
)
{
    uint64_t s0 = s4096[p4096];

    p4096 = ++p4096 & 63;

    uint64_t s1 = s4096[p4096];

    s0 ^= s0 >> 49;

    s1 ^= s1 << 25;
    s1 ^= s1 >> 3;

    s4096[p4096] = s0 ^ s1;

    return (s4096[p4096] * 8372773778140471301LL);
}