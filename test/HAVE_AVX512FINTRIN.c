#pragma GCC target("avx512f")
#include <immintrin.h>

void main()
{
    #ifndef __AVX512F__
    # error No AVX512 support
    #elif defined(__clang__)
    # if __clang_major__ < 4
    #  error Compiler AVX512 support may be broken
    # endif
    #elif defined(__GNUC__)
    # if __GNUC__ < 6
    #  error Compiler AVX512 support may be broken
    # endif
    #endif

    __m512i x = _mm512_setzero_epi32();
    __m512i y = _mm512_permutexvar_epi64(_mm512_setr_epi64(0, 1, 4, 5, 2, 3, 6, 7), x);
}