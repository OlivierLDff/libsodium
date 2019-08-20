#pragma GCC target("avx2")
#include <immintrin.h>

void main()
{
    __m256i y = _mm256_broadcastsi128_si256(_mm_setzero_si128());
}