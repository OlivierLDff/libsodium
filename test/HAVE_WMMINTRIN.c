#pragma GCC target("aes")
#pragma GCC target("pclmul")
#include <wmmintrin.h>

int main()
{
    __m128i x = _mm_aesimc_si128(_mm_setzero_si128());
    __m128i y = _mm_clmulepi64_si128(_mm_setzero_si128(), _mm_setzero_si128(), 0);

    return 0;
}