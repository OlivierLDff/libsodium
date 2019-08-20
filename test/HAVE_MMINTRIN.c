#pragma GCC target("mmx")
#include <mmintrin.h>

int main()
{
    __m64 x = _mm_setzero_si64();

    return 0;
}