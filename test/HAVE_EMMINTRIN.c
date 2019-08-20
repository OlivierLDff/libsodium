#pragma GCC target("sse2")
#ifndef __SSE2__
# define __SSE2__
#endif
#include <emmintrin.h>

void main()
{
    __m128d x = _mm_setzero_pd();
    __m128i z = _mm_srli_epi64(_mm_setzero_si128(), 26);
}