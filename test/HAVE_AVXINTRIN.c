#pragma GCC target("avx")
#include <immintrin.h>

int main()
{
    _mm256_zeroall();

    return 0;
}