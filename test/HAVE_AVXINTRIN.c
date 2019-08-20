#pragma GCC target("avx")
#include <immintrin.h>

void main()
{
    _mm256_zeroall();
}