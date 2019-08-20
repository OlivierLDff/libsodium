#pragma GCC target("avx2")
#include <immintrin.h>

int main()
{
    __m256i y = _mm256_broadcastsi128_si256(_mm_setzero_si128());
    return 0;
}